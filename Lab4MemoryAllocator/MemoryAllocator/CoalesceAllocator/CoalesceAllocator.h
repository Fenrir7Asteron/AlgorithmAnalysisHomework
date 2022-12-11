//
// Created by biore on 12/10/2022.
//

#ifndef LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H
#define LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H

#include "CoalescePage.h"

class CoalesceAllocator {
    friend class MemoryAllocator;
public:
    static size_t GetControlBlockSize();

private:
    CoalescePage *first_page_ = nullptr;
    int page_size_;

    void AllocFirstPage(int page_size);
    void AllocNewPage();
    void Destroy();

    void *Alloc(size_t request_size);

    static size_t GetAlignedMemorySize(size_t memory_size);

    bool Contains(void *p);

    void Free(void *p);

    bool HasFreeNeighbours(CoalesceBlockMetaData *block_p, CoalescePage *page);

    bool HasFreeLeftNeighbour(const CoalesceBlockMetaData *block_p) const;

    bool HasFreeRightNeighbour(CoalesceBlockMetaData *block_p, CoalescePage *page) const;
};


#endif //LAB4MEMORYALLOCATOR_COALESCEALLOCATOR_H
