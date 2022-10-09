//
// Created by biore on 10/9/2022.
//

#include "IntRange.h"

std::istream& operator>>(std::istream &is, IntRange& range) {
    return is >> range.start >> range.end;
}
