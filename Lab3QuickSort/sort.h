//
// Created by biore on 11/19/2022.
//

#include <iostream>

#ifndef LAB3QUICKSORT_SORT_H
#define LAB3QUICKSORT_SORT_H

const int INSERTION_SORT_IS_FASTER_BORDER = 14;

template<class T>
void move_swap(T& a, T& b)
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

template <typename T, typename Compare>
T *median_of_three(T *first, T *last, Compare comp) {
    T *middle = first + ((last - first + 1) / 2);

    if (comp(*last, *first))
        move_swap(*first, *last);

    if (comp(*middle, *first))
        move_swap(*middle, *first);

    if (comp(*last, *middle))
        move_swap(*last, *middle);

    return middle;
}



template<typename T, typename Compare>
T* partition(T *first, T *last, Compare comp) {
    // Select found_pivot
    T *found_pivot = median_of_three(first, last - 1, comp);

    T *i = first;
    T *j = last - 2;
    T *pivot_place = last - 1;

    // move found_pivot outside sorted range
    move_swap(*found_pivot, *pivot_place);

    // Sorting left and right parts of the found_pivot element
    while (i <= j) {
        while (i < pivot_place && comp(*i, *pivot_place)) {
            ++i;
        }

        while (j > first && comp(*pivot_place, *j)) {
            --j;
        }

        if (i <= j) {
            move_swap(*i, *j);
            ++i;
            --j;
        }
    }

    // put found_pivot to its place
    move_swap(*i, *pivot_place);
    return i;
}

template<typename T, typename Compare>
void insertion_sort(T *first, T *last, Compare comp) {
    for (auto step = first + 1; step < last; ++step) {
        auto key = *step;
        auto j = step - 1;

        // Compare key with each element on the left of it until an element smaller than it is found.
        while (comp(key, *j) && j >= first) {
            *(j + 1) = T(std::move(*j));
            --j;
        }

        if (j + 1 < step)
            *(j + 1) = T(std::move(key));
    }
}

template <typename T, typename Compare>
void sort(T *first, T *last, Compare comp)
{
    // base case
    while (last - first > 1)
    {
        if (last - first <= INSERTION_SORT_IS_FASTER_BORDER) {
            insertion_sort(first, last, comp);
            return;
        }

        T *p = partition(first, last, comp);

        // Sorting the smaller part recursively, while leaving the bigger part for iteration
        if (p - first < last - p) {
            // Sorting the left part recursively
            sort(first, p, comp);
            first = p;
        } else {
            // Sorting the right part recursively
            sort(p, last, comp);
            last = p;
        }
    }
}

#endif //LAB3QUICKSORT_SORT_H
