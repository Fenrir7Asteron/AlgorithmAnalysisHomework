//
// Created by biore on 12/8/2022.
//

#include "FSAPage.h"
#include "FSABlockMetaData.h"
#include <cmath>

void FSAPage::Init(const int block_count, const int block_size) {
    next_page = nullptr;
    free_list_header_ = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
    
    for (int block_idx = 0; block_idx < block_count; ++block_idx) {
        const unsigned long long actual_block_size = sizeof(FSABlockMetaData) + block_size;
        auto *block_meta_data = (FSABlockMetaData *) (((char *) this) + sizeof(FSAPage) + block_idx * actual_block_size);
        block_meta_data->next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
        block_meta_data->fsa_idx = sqrt(block_size) - sqrt(MIN_FSA_BLOCK_SIZE);
        block_meta_data->block_idx = block_idx;
    }
}
