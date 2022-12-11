//
// Created by biore on 12/10/2022.
//

#include "CoalesceAllocator.h"
#include "CoalesceBlockMetaData.h"
#include "../CommonBlockMetaData.h"
#include "../FSA/FSAPage.h"

void CoalesceAllocator::AllocFirstPage(const int page_size) {
    page_size_ = page_size;

    // Allocate enough memory to fit at least one alloc request. Max possible memory size request is equal to page_size.
    size_t page_size_with_metadata = page_size_ + sizeof(CoalescePage) + GetControlBlockSize();

    first_page_ = CoalescePage::AllocNewPage(page_size_with_metadata);
    first_page_->Init(page_size_with_metadata);
}

void CoalesceAllocator::AllocNewPage() {
    size_t page_size_with_metadata = page_size_ + sizeof(CoalescePage) + GetControlBlockSize();

    CoalescePage* last_page = first_page_;
    while (last_page->next_page != nullptr) {
        last_page = last_page->next_page;
    }

    last_page->next_page = CoalescePage::AllocNewPage(page_size_with_metadata);
    last_page->next_page->Init(0);
}

void CoalesceAllocator::Destroy() {
    CoalescePage *page = first_page_;
    do {
        auto *next_page = page->next_page;
        page->Free();
        page = next_page;
    } while(page != nullptr);
}

size_t CoalesceAllocator::GetControlBlockSize() {
    return GetAlignedMemorySize(sizeof(CoalesceBlockMetaData) + sizeof(CommonBlockMetaData));
}

void *CoalesceAllocator::Alloc(size_t request_size) {
    CoalescePage *page = first_page_;
    CoalesceBlockMetaData *free_block = nullptr;

    do {
        if (page->free_list_header == nullptr) {

            if (page->next_page == nullptr)
                AllocNewPage();
            page = page->next_page;

        } else {
            free_block = page->free_list_header;
        }
    } while (free_block == nullptr);

    if (free_block->block_size == 0) {
        free_block->block_size = page->GetRemainingPageMemory(free_block);
    }

    size_t required_memory = GetAlignedMemorySize(request_size + GetControlBlockSize());

    // First-fit search free block.
    while (required_memory > free_block->block_size && free_block->next_free_list_p != nullptr) {
        free_block = free_block->next_free_list_p;

        if (free_block->block_size == 0) {
            free_block->block_size = page->GetRemainingPageMemory(free_block);
        }
    }

    free_block->block_size = required_memory;

    if (free_block->next_free_list_p == nullptr) {
        CoalesceBlockMetaData* block_after_this_block_p = (CoalesceBlockMetaData*) (((char *) free_block) + required_memory);

        if (page->PointerIsInsidePage((char*) block_after_this_block_p)) {
            page->free_list_header = block_after_this_block_p;
            block_after_this_block_p->l_neighbour_p = free_block;

            if (free_block->prev_free_list_p != nullptr) {
                free_block->prev_free_list_p->next_free_list_p = block_after_this_block_p;
                block_after_this_block_p->prev_free_list_p = free_block->prev_free_list_p;
            }
        } else {
            page->free_list_header = nullptr;
        }

    } else {
        CoalesceBlockMetaData* block_after_this_block_p = free_block->next_free_list_p;
        page->free_list_header = block_after_this_block_p;

        if (free_block->prev_free_list_p != nullptr) {
            free_block->prev_free_list_p->next_free_list_p = block_after_this_block_p;
            block_after_this_block_p->prev_free_list_p = free_block->prev_free_list_p;
        }
    }

    void* used_data_p = (void *) ((char *) free_block + GetControlBlockSize());

    free_block->Occupy(used_data_p);

    return used_data_p;
}

size_t CoalesceAllocator::GetAlignedMemorySize(size_t memory_size) {
    return (memory_size - 1 + COALESCE_ALLOCATOR_MEMORY_ALIGNMENT) / COALESCE_ALLOCATOR_MEMORY_ALIGNMENT * COALESCE_ALLOCATOR_MEMORY_ALIGNMENT;
}

bool CoalesceAllocator::Contains(void *p) {
    CoalescePage *page = first_page_;

    while (page != nullptr) {

        if (page->Contains(p))
            return true;

        page = page->next_page;
    }
}

void CoalesceAllocator::Free(void *p) {
    CoalescePage *page = first_page_;

    while (page != nullptr) {

        if (page->Contains(p)) {
            auto *blockToFree = (CoalesceBlockMetaData *) ((char *) p - CoalesceAllocator::GetControlBlockSize());

            blockToFree->next_free_list_p = page->free_list_header;
            if (blockToFree->next_free_list_p != nullptr)
                blockToFree->next_free_list_p->prev_free_list_p = blockToFree;
            
            page->free_list_header = blockToFree;
            
            if (HasFreeRightNeighbour(blockToFree, page)) {
                CoalesceBlockMetaData *r_neighbour_p = blockToFree->GetRightNeighbourP();
                if (r_neighbour_p->prev_free_list_p != nullptr) {
                    r_neighbour_p->prev_free_list_p->next_free_list_p = r_neighbour_p->next_free_list_p;
                }

                if (r_neighbour_p->block_size == 0)
                    page->GetRemainingPageMemory(r_neighbour_p);
                    
                blockToFree->block_size += r_neighbour_p->block_size;
            }

            if (HasFreeLeftNeighbour(blockToFree)) {
                page->free_list_header = blockToFree->l_neighbour_p;
                blockToFree->Cleanup();
            }

            page->free_list_header->Unoccupy();

            break;
        }

        page = page->next_page;
    }
}

bool CoalesceAllocator::HasFreeRightNeighbour(CoalesceBlockMetaData *block_p, CoalescePage *page) const {
    CoalesceBlockMetaData *r_neighbour_p = block_p->GetRightNeighbourP();

    return page->PointerIsInsidePage((char*) r_neighbour_p) && r_neighbour_p != nullptr
           && r_neighbour_p->is_occupied == false;
}

bool
CoalesceAllocator::HasFreeLeftNeighbour(const CoalesceBlockMetaData *block_p) const {
    return block_p->l_neighbour_p != nullptr && block_p->l_neighbour_p->is_occupied == false;
}
