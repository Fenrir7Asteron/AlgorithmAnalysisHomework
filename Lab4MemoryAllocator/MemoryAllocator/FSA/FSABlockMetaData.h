//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
#define LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H

#include "../MemoryAllocatorConstants.h"

struct FSABlockMetaData {
    int next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
    int fsa_idx = -1;
};

#endif //LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
