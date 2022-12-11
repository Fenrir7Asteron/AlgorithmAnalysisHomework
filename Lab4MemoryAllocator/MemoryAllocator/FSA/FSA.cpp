//
// Created by biore on 12/8/2022.
//

#include <cassert>
#include "FSA.h"
#include "FSABlockMetaData.h"
#include "../CommonBlockMetaData.h"

FSA::FSA(int block_size) {
    block_size_ = block_size;
}

void FSA::AllocFirstPage(const int page_size) {
    page_size_ = page_size;

    int block_count = GetBlockCount();

    size_t page_size_with_metadata = block_count * (GetActualBlockSize()) + sizeof(FSAPage);

    first_page_ = FSAPage::AllocNewPage(page_size_with_metadata);
    first_page_->Init(block_count, block_size_);
}

void FSA::AllocNewPage() {
    int block_count = GetBlockCount();

    size_t page_size_with_metadata = block_count * (GetActualBlockSize()) + sizeof(FSAPage);

    FSAPage* last_page = first_page_;
    while (last_page->next_page != nullptr) {
        last_page = last_page->next_page;
    }

    last_page->next_page = FSAPage::AllocNewPage(page_size_with_metadata);
    last_page->next_page->Init(block_count, block_size_);
}

void FSA::Destroy() {
    FSAPage *page = first_page_;
    do {
        auto *next_page = page->next_page;
        page->Free();
        page = next_page;
    } while(page != nullptr);
}

int FSA::GetBlockCount() const { return page_size_ / block_size_; }

size_t FSA::GetActualBlockSize() const { return block_size_ + GetControlBlockSize(); }

void *FSA::Alloc() {
    FSAPage *page = first_page_;
    FSABlockMetaData *free_block = nullptr;

    do {
        if (page->free_list_header == NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE) {

            if (page->next_page == nullptr)
                AllocNewPage();
            page = page->next_page;

        } else if (page->free_list_header == NEXT_FREE_LIST_ITEM_NOT_ASSIGNED) {

            page->free_list_header = 0;
            free_block = (FSABlockMetaData *) ((char*) page + sizeof(FSAPage));

        } else {
            free_block = (FSABlockMetaData *) (((char *) page) + sizeof(FSAPage) + (page->free_list_header * GetActualBlockSize()));
        }
    } while (free_block == nullptr);

    int new_free_list_header = free_block->next_free_list_idx;

    if (new_free_list_header == NEXT_FREE_LIST_ITEM_NOT_ASSIGNED) {
        new_free_list_header = page->free_list_header + 1 < GetBlockCount()
            ? page->free_list_header + 1
            : NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE;
    }

    page->free_list_header = new_free_list_header;

    return (void*) ((char*) free_block + GetControlBlockSize());
}

void FSA::Free(void *p) {
    auto *blockToFree = (FSABlockMetaData*) ((char*) p - GetControlBlockSize());
    size_t actualBlockSize = GetActualBlockSize();
    int block_idx = blockToFree->block_idx;
    auto *page = (FSAPage*) ((char*) blockToFree - actualBlockSize * block_idx - sizeof(FSAPage));
    blockToFree->next_free_list_idx = page->free_list_header;
    page->free_list_header = block_idx;
}

size_t FSA::GetControlBlockSize() {
    return sizeof(FSABlockMetaData) + sizeof(CommonBlockMetaData);
}
