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
    size_t block_size = 0;
    bool is_occupied = false;
    void* user_data_p = nullptr;

    CoalesceBlockMetaData *GetRightNeighbourP() {
        return (CoalesceBlockMetaData *) ((char*) this + block_size);
    }

    void Cleanup() {
        next_free_list_p = nullptr;
        prev_free_list_p = nullptr;
        l_neighbour_p = nullptr;
        block_size = 0;
        is_occupied = false;
        user_data_p = nullptr;
    }

    void Occupy(void *p) {
        next_free_list_p = nullptr;
        prev_free_list_p = nullptr;
        user_data_p = p;
        is_occupied = true;
    }

    void Unoccupy() {
        is_occupied = false;
        user_data_p = nullptr;
    }
};


#endif //LAB4MEMORYALLOCATOR_COALESCEBLOCKMETADATA_H
