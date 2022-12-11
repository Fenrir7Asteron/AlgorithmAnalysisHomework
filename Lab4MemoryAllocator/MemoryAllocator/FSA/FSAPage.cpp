//
// Created by biore on 12/8/2022.
//

#include "FSAPage.h"
#include "FSABlockMetaData.h"
#include <cmath>
#include <cassert>
#include <algorithm>

void FSAPage::Init(const int block_count, const int block_size) {
    next_page = nullptr;
    free_list_header = std::max(1, (int) sizeof(FSAPage) / block_size);
    page_size_ = block_count * block_size;
    block_size_ = block_size;

    for (int block_idx = free_list_header; block_idx < block_count; ++block_idx) {
        auto *fsa_block_meta_data = (FSABlockMetaData *) (((char *) this) + block_idx * block_size);

        if (block_idx + 1 < block_count)
            fsa_block_meta_data->next_free_list_idx = block_idx + 1;
        else
            fsa_block_meta_data->next_free_list_idx = NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE;

        fsa_block_meta_data->fsa_idx = sqrt(block_size) - sqrt(MIN_FSA_BLOCK_SIZE);
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

bool FSAPage::Contains(void *p) {
    unsigned long p_offset_from_page = ((char *) p) - ((char *) this);
    bool is_block_aligned = p_offset_from_page / block_size_ * block_size_ == p_offset_from_page;
    bool is_inside_page = p_offset_from_page < page_size_;
    return is_inside_page && is_block_aligned;
}
