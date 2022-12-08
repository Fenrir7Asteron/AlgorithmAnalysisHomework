//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
#define LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H

#include "FSAConstants.h"

struct FSABlockMetaData {
public:
    int next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
};

#endif //LAB4MEMORYALLOCATOR_FSABLOCKMETADATA_H
