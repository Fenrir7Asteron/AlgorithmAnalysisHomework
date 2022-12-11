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
    return sizeof(CoalesceBlockMetaData) + sizeof(CommonBlockMetaData);
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

    free_block->block_size = request_size + GetControlBlockSize();

    if (free_block->next_free_list_p == nullptr) {
        char *block_after_this_block_p = ((char *) free_block) + GetControlBlockSize() + request_size;
        if (page->PointerIsInsidePage(block_after_this_block_p)) {
            page->free_list_header = (CoalesceBlockMetaData*) block_after_this_block_p;
//            free_block->prev_free_list_p =
        } else {
            page->free_list_header = nullptr;
        }

    } else {
        page->free_list_header = free_block->next_free_list_p;
    }

    return (void*) ((char*) free_block + GetControlBlockSize());
}
