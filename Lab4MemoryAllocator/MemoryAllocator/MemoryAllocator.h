//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
#define LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H

#include "FSA/FSA.h"
#include "CoalesceAllocator/CoalesceAllocator.h"


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
    const int FSAPageSize = 1024 * 1024; // 1MB
    const int CoalesceAllocatorPageSize = 20 * 1024 * 1024; // 20MB
    bool is_destroyed_;

    FSA fsa_list_[FSACount];
    CoalesceAllocator coalesce_allocator_;

    void DestroyFSA();
};


#endif //LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
