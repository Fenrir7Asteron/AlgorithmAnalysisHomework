//
// Created by biore on 12/10/2022.
//

#include <cassert>
#include "CoalescePage.h"

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
