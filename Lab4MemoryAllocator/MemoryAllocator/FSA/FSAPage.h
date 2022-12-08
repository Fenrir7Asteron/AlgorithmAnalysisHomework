//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSAPAGE_H
#define LAB4MEMORYALLOCATOR_FSAPAGE_H


#include "FSAConstants.h"

class FSAPage {
public:
    FSAPage *next_page;
    int free_list_header_;

    void Init(const int block_count, const int block_size);
};


#endif //LAB4MEMORYALLOCATOR_FSAPAGE_H
