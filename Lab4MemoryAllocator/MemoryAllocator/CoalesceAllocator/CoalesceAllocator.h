//
// Created by biore on 12/10/2022.
//

#ifndef LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H
#define LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H


#include "CoalescePage.h"

class CoalesceAllocator {
    friend class MemoryAllocator;
public:

private:
    CoalescePage *first_page_ = nullptr;
    int block_size_;
    int page_size_;

    void AllocFirstPage(int page_size);
    void AllocNewPage();
    void Destroy();

    static size_t GetControlBlockSize();

    void *Alloc(size_t request_size);
};


#endif //LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H
