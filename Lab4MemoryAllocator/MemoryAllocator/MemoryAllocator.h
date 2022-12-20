//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
#define LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H

#include <vector>
#include "FSA/FSA.h"
#include "CoalesceAllocator/CoalesceAllocator.h"
#include "OccupiedBlock.h"


class MemoryAllocator {
#ifdef DEBUG
    friend class CoalesceAllocator;
#endif
public:
    MemoryAllocator();
    virtual ~MemoryAllocator();
    virtual void init();
    virtual void destroy();
    virtual void *alloc(size_t size);
    virtual void free(void *p);

#ifdef DEBUG
    virtual void dumpStat() const;
    virtual void dumpBlocks() const;
#endif

private:
    static const int FSACount = 6;
    const int FSAPageSize = 1024 * 1024; // 1MB
    const int CoalesceAllocatorPageSize = 20 * 1024 * 1024; // 20MB

    FSA fsa_list_[FSACount];
    CoalesceAllocator coalesce_allocator_;

    // Stores only OS allocated block in release and all blocks in debug.
    static std::vector<OccupiedBlock> occupied_blocks_;

    static void AddOccupiedBlockToTrackedList(void *p, const size_t block_size, const int allocator_type);
    static void RemoveOccupiedBlockFromTrackedList(void *p);

#ifdef DEBUG
    bool is_initialized_ = false;
    bool is_destroyed_ = false;
    static void PrintFSAAllocatedBlocks();
    static void PrintCoalesceAllocatedBlocks();
    static void PrintWindowsAllocatedBlocks();
    static bool AllocatorContainsBlock(void *p);
#endif

    void DestroyFSA();

    void DestroyCoalesceAllocator();

    void DestroyWindowsAllocator();
};


#endif //LAB4MEMORYALLOCATOR_MEMORYALLOCATOR_H
