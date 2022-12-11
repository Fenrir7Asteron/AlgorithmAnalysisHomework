//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
#define LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H

#include "../MemoryAllocatorConstants.h"

struct FSABlockMetaData {
    unsigned char next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
    unsigned char fsa_idx = -1;
    unsigned char block_idx = -1;
};

#endif //LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
