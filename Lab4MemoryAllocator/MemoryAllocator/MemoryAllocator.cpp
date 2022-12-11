//
// Created by biore on 12/8/2022.
//

#include "MemoryAllocator.h"
#include "FSA/FSABlockMetaData.h"
#include "CommonBlockMetaData.h"

MemoryAllocator::~MemoryAllocator() {
    DestroyFSA();
}

void MemoryAllocator::init() {
    for (auto & fsa : fsa_list_)
        fsa.AllocFirstPage(PageSizeBytes);
}

void MemoryAllocator::destroy() {
    DestroyFSA();
}

MemoryAllocator::MemoryAllocator() :
    fsa_list_ {FSA(16), FSA(32), FSA(64),
    FSA(128), FSA(256), FSA(512)},
    coalesce_allocator_()
    {}

void *MemoryAllocator::alloc(size_t size) {
    for (FSA & fsa : fsa_list_) {
        if (fsa.block_size_ >= size)
            return fsa.Alloc();
    }
    
    if (size <= MAX_COALESCE_REQUEST_SIZE) {
        coalesce_allocator_.Alloc(size);
    }
}

void *MemoryAllocator::free(void *p) {

    auto *commonBlockMetaData = (CommonBlockMetaData*) ((char*) p - sizeof(CommonBlockMetaData));

    if (commonBlockMetaData->type_of_allocator == FSA_ALLOCATOR) {
        auto *blockToFree = (FSABlockMetaData*) ((char*) p - FSA::GetControlBlockSize());
        fsa_list_[blockToFree->fsa_idx].Free(p);
    }
}

void MemoryAllocator::DestroyFSA() {
    for (auto & fsa : fsa_list_)
        fsa.Destroy();
}
