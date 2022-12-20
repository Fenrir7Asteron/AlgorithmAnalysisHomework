//
// Created by biore on 12/20/2022.
//

#ifndef LAB4MEMORYALLOCATOR_OCCUPIEDBLOCK_H
#define LAB4MEMORYALLOCATOR_OCCUPIEDBLOCK_H

#include "corecrt.h"

struct OccupiedBlock {
public:
    static const int FSA_ALLOCATOR_TYPE_ID = 0;
    static const int COALESCE_ALLOCATOR_TYPE_ID = 1;
    static const int VIRTUAL_ALLOC_ALLOCATOR_TYPE_ID = 2;

    void* p;
    size_t block_size;
    int allocator_type;

    OccupiedBlock(void *p, const size_t block_size, const int allocator_type) {
        this->p = p;
        this->block_size = block_size;
        this->allocator_type = allocator_type;
    }
};

#endif //LAB4MEMORYALLOCATOR_OCCUPIEDBLOCK_H
