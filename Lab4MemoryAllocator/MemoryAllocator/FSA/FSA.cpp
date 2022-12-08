//
// Created by biore on 12/8/2022.
//

#include "FSA.h"
#include "FSABlockMetaData.h"

void FSA::AllocFirstPage(const int page_size) {
    page_size_ = page_size;

    int block_count = GetBlockCount();

    size_t page_size_with_block_metadata = block_count * (GetActualBlockSize());
    first_page_ = (FSAPage*) VirtualAlloc(first_page_, page_size_with_block_metadata, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    first_page_->Init(block_count, block_size_);
}

int FSA::GetBlockCount() const { return page_size_ / block_size_; }

size_t FSA::GetActualBlockSize() const { return sizeof(FSABlockMetaData) + block_size_; }

void FSA::AllocNewPage(int page_size) {
    FSAPage *page = first_page_;

    while (page->next_page != nullptr)
        page = page->next_page;

    page->next_page = (FSAPage*) VirtualAlloc(page->next_page, page_size + sizeof(FSAPage), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

FSA::FSA(int block_size) {
    block_size_ = block_size;
}

void *FSA::Alloc() {
    FSAPage *page = first_page_;
    FSABlockMetaData *free_block = nullptr;

    do {
        if (page->free_list_header_ == NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE) {
            page = page->next_page;
        } else if (page->free_list_header_ == NEXT_FREE_LIST_ITEM_NOT_ASSIGNED) {
            page->free_list_header_ = 0;
            free_block = (FSABlockMetaData *) page;
        } else {
            free_block = (FSABlockMetaData *) ((char *) page) + (page->free_list_header_ * GetActualBlockSize());
        }
    } while (free_block == nullptr);

    int new_free_list_header = free_block->next_free_list_idx;

    if (new_free_list_header == NEXT_FREE_LIST_ITEM_NOT_ASSIGNED) {
        new_free_list_header = page->free_list_header_ + 1 < GetBlockCount()
            ? page->free_list_header_ + 1
            : NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE;
    }

    page->free_list_header_ = new_free_list_header;

    return (void*) ((char*) free_block + sizeof(FSABlockMetaData));
}
