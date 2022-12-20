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
    int free_list_header;
    size_t page_size_;
    int block_size_;

    static FSAPage *AllocNewPage(size_t page_size);
    void Init(const int block_count, const int block_size);

    void Free();

    bool Contains(void *p);

    static const int &GetNumberOfControlBlocks(const int block_size) ;
};


#endif //LAB4MEMORYALLOCATOR_FSAPAGE_H
