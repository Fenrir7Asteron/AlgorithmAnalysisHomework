//
// Created by biore on 12/8/2022.
//

#include <cassert>
#include "MemoryAllocator.h"

#if DEBUG
#include <iostream>
#endif

std::vector<OccupiedBlock> MemoryAllocator::occupied_blocks_ = {};

MemoryAllocator::MemoryAllocator() :
        fsa_list_ {FSA(16), FSA(32), FSA(64),
                   FSA(128), FSA(256), FSA(512)},
        coalesce_allocator_()
{}

MemoryAllocator::~MemoryAllocator() {
    assert(!is_initialized_);
    assert(is_destroyed_);
}

void MemoryAllocator::init() {
    assert(!is_initialized_);

    for (auto & fsa : fsa_list_)
        fsa.AllocFirstPage(FSAPageSize);

    coalesce_allocator_.AllocFirstPage(CoalesceAllocatorPageSize);

#if DEBUG
    is_initialized_ = true;
    is_destroyed_ = false;
#endif
}

void MemoryAllocator::destroy() {
    assert(is_initialized_);
    assert(!is_destroyed_);
    assert(occupied_blocks_.empty() && "Memory leak detected. Some memory has not been freed before allocator destruction.");

    DestroyFSA();
    DestroyCoalesceAllocator();
    DestroyWindowsAllocator();

    occupied_blocks_.clear();

#if DEBUG
    is_initialized_ = false;
    is_destroyed_ = true;
#endif
}

void *MemoryAllocator::alloc(size_t size) {
    assert(is_initialized_);

    for (FSA & fsa : fsa_list_) {
        if (fsa.block_size_ >= size) {
            void *allocated_block = fsa.Alloc();

#if DEBUG
            AddOccupiedBlockToTrackedList(allocated_block, size, OccupiedBlock::FSA_ALLOCATOR_TYPE_ID);
#endif

            return allocated_block;
        }
    }
    
    if (size <= MAX_COALESCE_REQUEST_SIZE) {
        coalesce_allocator_.Alloc(size);
    } else {
        void *p = nullptr;
        p = VirtualAlloc(p, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        assert(p != nullptr);

        AddOccupiedBlockToTrackedList(p, size, OccupiedBlock::VIRTUAL_ALLOC_ALLOCATOR_TYPE_ID);

        return p;
    }
}

void MemoryAllocator::free(void *p) {
    assert(is_initialized_);
    assert(AllocatorContainsBlock(p) && "Tried to free with pointer that does not point to a start of any allocated block");

    for (FSA & fsa : fsa_list_) {
        if (fsa.Contains(p)) {
#if DEBUG
            RemoveOccupiedBlockFromTrackedList(p);
#endif

            fsa.Free(p);
            return;
        }
    }

    if (coalesce_allocator_.Contains(p)) {
        coalesce_allocator_.Free(p);
#if DEBUG
        RemoveOccupiedBlockFromTrackedList(p);
#endif
        return;
    }

    assert(VirtualFree(p, 0, MEM_RELEASE) != 0);
    RemoveOccupiedBlockFromTrackedList(p);
}

void MemoryAllocator::DestroyFSA() {
    for (auto & fsa : fsa_list_)
        fsa.Destroy();
}

void MemoryAllocator::DestroyCoalesceAllocator() { coalesce_allocator_.Destroy(); }

void MemoryAllocator::DestroyWindowsAllocator() {
    for (const auto &block : occupied_blocks_) {
        if (block.allocator_type != OccupiedBlock::VIRTUAL_ALLOC_ALLOCATOR_TYPE_ID)
            continue;

        WINBOOL result = VirtualFree(block.p, 0, MEM_RELEASE);
        assert(result != 0);
    }
}

void MemoryAllocator::AddOccupiedBlockToTrackedList(void *p, const size_t block_size, const int allocator_type) {
    occupied_blocks_.emplace_back(OccupiedBlock(p, block_size, allocator_type));
}

void MemoryAllocator::RemoveOccupiedBlockFromTrackedList(void *p) {
    for (int idx = 0; idx < occupied_blocks_.size(); ++idx) {
        OccupiedBlock &block = occupied_blocks_[idx];
        if (block.p == p) {
            occupied_blocks_.erase(occupied_blocks_.begin() + idx);
            break;
        }
    }
}

#ifdef DEBUG

void MemoryAllocator::dumpStat() const {
    assert(is_initialized_);
    assert(!is_destroyed_);

    printf("=========Memory Allocator Stats=========\n");

    printf("---------FSA---------\n");

    for (const FSA & fsa : fsa_list_) {
        fsa.DumpStat();
    }

    printf("---------Coalesce Allocator---------\n");

    coalesce_allocator_.DumpStat();


    printf("---------Windows Virtual Allocator---------\n");

    PrintWindowsAllocatedBlocks();

    printf("=======================================\n");
}

void MemoryAllocator::dumpBlocks() const {
    assert(is_initialized_);
    assert(!is_destroyed_);

    printf("=========Memory Allocator Blocks=========\n");

    printf("---------FSA---------\n");

    PrintFSAAllocatedBlocks();

    printf("---------Coalesce Allocator---------\n");

    PrintCoalesceAllocatedBlocks();

    printf("---------Windows Virtual Allocator---------\n");

    PrintWindowsAllocatedBlocks();

    printf("=======================================\n");
}

void MemoryAllocator::PrintFSAAllocatedBlocks() {
    int occupied_blocks_count = 0;

    for (auto & block : occupied_blocks_) {
        if (block.allocator_type != OccupiedBlock::FSA_ALLOCATOR_TYPE_ID)
            continue;

        occupied_blocks_count++;

        if (occupied_blocks_count == 1)
            printf("FSA occupied blocks:\n");

        printf("FSA occupied block address %p size %d\n", block.p, block.block_size);
    }

    printf("FSA occupied blocks count: %d\n", occupied_blocks_count);
}

void MemoryAllocator::PrintCoalesceAllocatedBlocks() {
    int occupied_blocks_count = 0;

    for (auto & block : occupied_blocks_) {
        if (block.allocator_type != OccupiedBlock::VIRTUAL_ALLOC_ALLOCATOR_TYPE_ID)
            continue;

        occupied_blocks_count++;

        if (occupied_blocks_count == 1)
            printf("Coalesce allocator occupied blocks:\n");

        printf("Coalesce allocator occupied block address %p size %d\n", block.p, block.block_size);
    }

    printf("Coalesce allocator occupied blocks count: %d\n", occupied_blocks_count);
}

void MemoryAllocator::PrintWindowsAllocatedBlocks() {
    int occupied_blocks_count = 0;

    for (auto & block : occupied_blocks_) {
        if (block.allocator_type != OccupiedBlock::VIRTUAL_ALLOC_ALLOCATOR_TYPE_ID)
            continue;

        occupied_blocks_count++;

        if (occupied_blocks_count == 1)
            printf("Windows virtual allocator occupied blocks:\n");

        printf("Windows virtual allocator occupied block address %p size %d\n", block.p, block.block_size);
    }

    printf("Windows virtual allocator occupied blocks count: %d\n", occupied_blocks_count);
}

bool MemoryAllocator::AllocatorContainsBlock(void *p) {
    for (auto & block : occupied_blocks_) {
        if (block.p == p)
            return true;
    }

    return false;
}

#endif


