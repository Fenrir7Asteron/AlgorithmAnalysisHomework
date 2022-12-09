//
// Created by biore on 12/8/2022.
//

#include "MemoryAllocator.h"
#include "FSA/FSABlockMetaData.h"

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

MemoryAllocator::MemoryAllocator() : fsa_list_ {
    FSA(16), FSA(32), FSA(64),
    FSA(128), FSA(256), FSA(512)} {
}

void *MemoryAllocator::alloc(size_t size) {
    for (FSA & fsa : fsa_list_) {
        if (fsa.block_size_ >= size)
            return fsa.Alloc();
    }
}

void *MemoryAllocator::free(void *p) {
    auto *blockToFree = (FSABlockMetaData*) ((char*) p - sizeof(FSABlockMetaData));
    size_t actualBlockSize = fsa_list_[blockToFree->fsa_idx].GetActualBlockSize();
    int block_idx = blockToFree->block_idx;
    auto *page = (FSAPage*) ((char*) blockToFree - actualBlockSize * block_idx - sizeof(FSAPage));
    blockToFree->next_free_list_idx = page->free_list_header_;
    page->free_list_header_ = block_idx;
}

void MemoryAllocator::DestroyFSA() {
    for (auto & fsa : fsa_list_)
        fsa.Destroy();
}
