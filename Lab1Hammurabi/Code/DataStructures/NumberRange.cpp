//
// Created by biore on 10/9/2022.
//

#include "NumberRange.h"

std::istream& operator>>(std::istream &is, NumberRange<int>& range) {
    return is >> range.start >> range.end;
}

std::istream& operator>>(std::istream &is, NumberRange<float>& range) {
    return is >> range.start >> range.end;
}