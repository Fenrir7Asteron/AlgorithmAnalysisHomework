//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
#define LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H

#include "FSA/FSA.h"

class MemoryAllocator {
public:
    MemoryAllocator();
    virtual void init();
    virtual void *alloc(size_t size);

private:
    static const int FSACount = 6;
    const int PageSizeBytes = 2048;

    FSA fsa_list_[FSACount];
};


#endif //LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
