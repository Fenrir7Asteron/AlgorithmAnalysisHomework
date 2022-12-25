//
// Created by biore on 12/10/2022.
//

#ifndef LAB4MEMORYALLOCATOR_COALESCEPAGE_H
#define LAB4MEMORYALLOCATOR_COALESCEPAGE_H

#include "../MemoryAllocatorConstants.h"
#include "memoryapi.h"
#include "CoalesceBlockMetaData.h"

class CoalescePage {
public:
    CoalescePage *next_page;
    CoalesceBlockMetaData* free_list_header;

    static CoalescePage *AllocNewPage(size_t page_size);
    void Init(size_t page_size);

    void Free();

    bool PointerIsInsidePage(const char *p);

    bool Contains(void *p);

    size_t GetRemainingPageMemory(CoalesceBlockMetaData *block_p);

private:
    size_t page_size_;
};


#endif //LAB4MEMORYALLOCATOR_COALESCEPAGE_H
