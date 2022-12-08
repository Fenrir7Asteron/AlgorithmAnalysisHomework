//
// Created by biore on 12/8/2022.
//

#include "MemoryAllocator.h"

void MemoryAllocator::init() {
    fsa_list_[0].AllocFirstPage(PageSizeBytes);

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
