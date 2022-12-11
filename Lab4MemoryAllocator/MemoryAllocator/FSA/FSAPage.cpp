//
// Created by biore on 12/8/2022.
//

#include "FSAPage.h"
#include "FSABlockMetaData.h"
#include "../CommonBlockMetaData.h"
#include "FSA.h"
#include <cmath>
#include <cassert>

void FSAPage::Init(const int block_count, const int block_size) {
    next_page = nullptr;
    free_list_header = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;

    for (int block_idx = 0; block_idx < block_count; ++block_idx) {
        const unsigned long long actual_block_size = block_size + FSA::GetControlBlockSize();

        auto *fsa_block_meta_data = (FSABlockMetaData *) (((char *) this) + sizeof(FSAPage) + block_idx * actual_block_size);
        fsa_block_meta_data->next_free_list_idx = NEXT_FREE_LIST_ITEM_NOT_ASSIGNED;
        fsa_block_meta_data->fsa_idx = sqrt(block_size) - sqrt(MIN_FSA_BLOCK_SIZE);
        fsa_block_meta_data->block_idx = block_idx;

        auto *common_block_meta_data = (CommonBlockMetaData *) (((char *) fsa_block_meta_data) + sizeof(FSABlockMetaData));
        common_block_meta_data->type_of_allocator = FSA_ALLOCATOR;
    }
}

FSAPage *FSAPage::AllocNewPage(size_t page_size) {
    FSAPage* page = nullptr;
    page = (FSAPage*) VirtualAlloc(page, page_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    assert(page != nullptr);
    return page;
}

void FSAPage::Free() {
    assert(VirtualFree(this, 0, MEM_RELEASE) != 0);
}
