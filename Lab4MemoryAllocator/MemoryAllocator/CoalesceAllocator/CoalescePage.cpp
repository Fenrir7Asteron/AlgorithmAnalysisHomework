//
// Created by biore on 12/10/2022.
//

#include <cassert>
#include "CoalescePage.h"
#include "CoalesceAllocator.h"

void CoalescePage::Init(size_t page_size) {
    next_page = nullptr;
    free_list_header = (CoalesceBlockMetaData*) (((char*) this) + sizeof(CoalescePage));
    page_size_ = page_size;
}

CoalescePage *CoalescePage::AllocNewPage(size_t page_size) {
    CoalescePage* page = nullptr;
    page = (CoalescePage*) VirtualAlloc(page, page_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    assert(page != nullptr);
    return page;
}

void CoalescePage::Free() {
    assert(VirtualFree(this, 0, MEM_RELEASE) != 0);
}

bool CoalescePage::PointerIsInsidePage(const char *p) {
    return (p - ((char*) this)) < page_size_;
}

bool CoalescePage::Contains(void *p) {
    unsigned long p_offset_from_page = ((char *) p) - ((char *) this);
    bool is_block_aligned = p_offset_from_page / COALESCE_ALLOCATOR_MEMORY_ALIGNMENT * COALESCE_ALLOCATOR_MEMORY_ALIGNMENT == p_offset_from_page;
    
    if (PointerIsInsidePage((char*) p) && is_block_aligned) {
        char *block_p = (char *) p - CoalesceAllocator::GetControlBlockSize();

        if (!PointerIsInsidePage(block_p))
            return false;

        auto *control_block = (CoalesceBlockMetaData *) block_p;

        if (control_block->user_data_p == p)
            return true;
    }

    return false;
}

size_t CoalescePage::GetRemainingPageMemory(CoalesceBlockMetaData *block_p) {
    unsigned long block_offset_from_page = (char *) block_p - (char *) this;
    return page_size_ - block_offset_from_page;
}
