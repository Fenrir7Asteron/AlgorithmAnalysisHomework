//
// Created by biore on 10/9/2022.
//

#ifndef LAB1HAMMURABI_NUMBERRANGE_H
#define LAB1HAMMURABI_NUMBERRANGE_H


#include <fstream>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
requires Number<T>
class NumberRange {
public:
    T start, end;

    friend std::istream& operator>>(std::istream &is, NumberRange<int>& range);
    friend std::istream& operator>>(std::istream &is, NumberRange<float>& range);
};


#endif //LAB1HAMMURABI_NUMBERRANGE_H
