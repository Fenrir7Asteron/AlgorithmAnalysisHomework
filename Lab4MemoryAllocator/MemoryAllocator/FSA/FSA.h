//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSA_H
#define LAB4MEMORYALLOCATOR_FSA_H


#include "FSAPage.h"

class FSA {
    explicit FSA(int block_size);

    friend class MemoryAllocator;
public:

    static size_t GetControlBlockSize();

private:
    FSAPage *first_page_ = nullptr;
    int block_size_;
    int page_size_;

    void AllocFirstPage(int page_size);
    void AllocNewPage();
    void Destroy();

    void *Alloc();

    size_t GetActualBlockSize() const;

    int GetBlockCount() const;

    void Free(void *p);

    bool Contains(void *p);
};


#endif //LAB4MEMORYALLOCATOR_FSA_H
