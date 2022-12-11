//
// Created by biore on 12/10/2022.
//

#ifndef LAB4MEMORYALLOCATOR_COALESCEBLOCKMETADATA_H
#define LAB4MEMORYALLOCATOR_COALESCEBLOCKMETADATA_H


#include "../MemoryAllocatorConstants.h"

struct CoalesceBlockMetaData {
    CoalesceBlockMetaData* next_free_list_p = nullptr;
    CoalesceBlockMetaData* prev_free_list_p = nullptr;
    CoalesceBlockMetaData* l_neighbour_p = nullptr;
    CoalesceBlockMetaData* r_neighbour_p = nullptr;
    void* page_start_p = nullptr;
    size_t block_size;
};


#endif //LAB4MEMORYALLOCATOR_COALESCEBLOCKMETADATA_H
