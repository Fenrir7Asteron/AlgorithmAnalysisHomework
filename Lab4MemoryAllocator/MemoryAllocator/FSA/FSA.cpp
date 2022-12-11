//
// Created by biore on 12/8/2022.
//

#include "FSA.h"
#include "FSABlockMetaData.h"

FSA::FSA(int block_size) {
    block_size_ = block_size;
}

void FSA::AllocFirstPage(const int page_size) {
    page_size_ = page_size;

    first_page_ = FSAPage::AllocNewPage(page_size_);
    first_page_->Init(GetBlockCount(), block_size_);
}

void FSA::AllocNewPage() {
    FSAPage* last_page = first_page_;
    while (last_page->next_page != nullptr) {
        last_page = last_page->next_page;
    }

    last_page->next_page = FSAPage::AllocNewPage(page_size_);
    last_page->next_page->Init(GetBlockCount(), block_size_);
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

void *FSA::Alloc() {
    FSAPage *page = first_page_;
    FSABlockMetaData *free_block = nullptr;

    do {
        if (page->free_list_header == NEXT_FREE_LIST_ITEM_IS_OUT_OF_RANGE) {

            if (page->next_page == nullptr)
                AllocNewPage();
            page = page->next_page;

        } else {
            free_block = (FSABlockMetaData *) (((char *) page) + (page->free_list_header * block_size_));
        }
    } while (free_block == nullptr);

    page->free_list_header = free_block->next_free_list_idx;

    return (void*) free_block;
}

void FSA::Free(void *p) {
    FSAPage *page = first_page_;

    while (page != nullptr) {

        if (page->Contains(p)) {
            auto *blockToFree = (FSABlockMetaData*) p;

            unsigned long p_offset_from_page = ((char *) p) - ((char *) page);
            int block_idx = (int) (p_offset_from_page / block_size_);

            blockToFree->next_free_list_idx = page->free_list_header;
            page->free_list_header = block_idx;

            break;
        }

        page = page->next_page;
    }
}

bool FSA::Contains(void *p) {
    FSAPage *page = first_page_;
    
    while (page != nullptr) {

        if (page->Contains(p))
            return true;

        page = page->next_page;
    }
}
