//
// Created by biore on 12/8/2022.
//

#include "FSAPage.h"
#include "FSABlockMetaData.h"

void FSAPage::Init(const int block_count, const int block_size) {
    next_page = nullptr;
    free_list_header_ = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
    
    for (int i = 0; i < block_count; ++i) {
        const unsigned long long actual_block_size = sizeof(FSABlockMetaData) + block_size;
        auto *block_meta_data = (FSABlockMetaData *) (((char *) this) + i * actual_block_size);
        block_meta_data->next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
    }
}
