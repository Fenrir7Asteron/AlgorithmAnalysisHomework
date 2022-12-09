//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
#define LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H

#include "FSA/FSA.h"

class MemoryAllocator {
public:
    MemoryAllocator();
    virtual ~MemoryAllocator();
    virtual void init();
    virtual void destroy();
    virtual void *alloc(size_t size);
    virtual void *free(void *p);

private:
    static const int FSACount = 6;
    const int PageSizeBytes = 2048;

    FSA fsa_list_[FSACount];

    void DestroyFSA();
};


#endif //LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
