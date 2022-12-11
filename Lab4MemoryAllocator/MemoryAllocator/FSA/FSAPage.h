//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSAPAGE_H
#define LAB4MEMORYALLOCATOR_FSAPAGE_H


#include "../MemoryAllocatorConstants.h"
#include "memoryapi.h"

class FSAPage {
public:
    FSAPage *next_page;
    unsigned int free_list_header;

    static FSAPage *AllocNewPage(size_t page_size);
    void Init(const int block_count, const int block_size);

    void Free();
};


#endif //LAB4MEMORYALLOCATOR_FSAPAGE_H
