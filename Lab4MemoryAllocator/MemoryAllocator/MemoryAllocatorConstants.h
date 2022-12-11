//
// Created by biore on 12/8/2022.
//

#ifndef LAB4MEMORYALLOCATOR_MEMORYALLOCATORCONSTANTS_H
#define LAB4MEMORYALLOCATOR_MEMORYALLOCATORCONSTANTS_H

// FSA constants
static const unsigned char NEXT_FREE_LIST_ITEM_NOT_ASSIGNED = -1;
static const unsigned char NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE = -2;
static const unsigned char MIN_FSA_BLOCK_SIZE = 16;

// Coalesce allocator constants
static const int MAX_COALESCE_REQUEST_SIZE = 1024 * 1024 * 10;

static const unsigned char FSA_ALLOCATOR = 0;
static const unsigned char COALESCE_ALLOCATOR = 1;

#endif //LAB4MEMORYALLOCATOR_MEMORYALLOCATORCONSTANTS_H
