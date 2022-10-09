//
// Created by biore on 10/9/2022.
//

#ifndef LAB1HAMMURABI_INTRANGE_H
#define LAB1HAMMURABI_INTRANGE_H


#include <fstream>

class IntRange {
public:
    int start, end;

    friend std::istream& operator>>(std::istream &is, IntRange& range);
};


#endif //LAB1HAMMURABI_INTRANGE_H
