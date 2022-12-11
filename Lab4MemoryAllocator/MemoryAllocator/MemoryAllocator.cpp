//
// Created by biore on 12/8/2022.
//

#include <cassert>
#include "MemoryAllocator.h"
#include "iostream"

MemoryAllocator::~MemoryAllocator() {
    assert(is_destroyed_);
}

void MemoryAllocator::init() {
    for (auto & fsa : fsa_list_)
        fsa.AllocFirstPage(PageSizeBytes);
}

void MemoryAllocator::destroy() {
    DestroyFSA();
    is_destroyed_ = true;
}

MemoryAllocator::MemoryAllocator() :
    fsa_list_ {FSA(16), FSA(32), FSA(64),
    FSA(128), FSA(256), FSA(512)},
    coalesce_allocator_()
    {}

void *MemoryAllocator::alloc(size_t size) {
    for (FSA & fsa : fsa_list_) {
        if (fsa.block_size_ >= size) {
            return fsa.Alloc();
        }
    }
    
    if (size <= MAX_COALESCE_REQUEST_SIZE) {
        coalesce_allocator_.Alloc(size);
    }
}

void *MemoryAllocator::free(void *p) {
    for (FSA & fsa : fsa_list_) {
        if (fsa.Contains(p)) {
            fsa.Free(p);
            break;
        }
    }
}

void MemoryAllocator::DestroyFSA() {
    for (auto & fsa : fsa_list_)
        fsa.Destroy();
}
