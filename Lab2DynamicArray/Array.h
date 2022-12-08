//
// Created by biore on 11/13/2022.
//

#ifndef LAB2DYNAMICARRAY_ARRAY_H
#define LAB2DYNAMICARRAY_ARRAY_H

#include <iostream>
#include <cassert>

template<typename T>
class Array final {
public:
    Array() {
        capacity_ = 0;
        size_ = 0;
        array_ = nullptr;
    }

    explicit Array(int capacity) {
        capacity_ = capacity;
        size_ = 0;
        array_ = (T*) malloc((capacity_ * sizeof(T)));
    }

    Array(const Array<T>& other) {
        capacity_ = other.capacity_;
        size_ = other.size();
        T* new_array = (T*) malloc((capacity_ * sizeof(T)));

        for (int i = 0; i < other.size(); ++i) {
            new (new_array + i) T(std::move(other[i]));
        }

        array_ = new_array;
    }

    Array(Array<T>&& other)  noexcept {
        capacity_ = other.capacity_;
        size_ = other.size();
        array_ = other.array_;

        other.array_ = nullptr;
        other.size_ = 0;
    }

    ~Array() {
        for (int i = 0; i < size_; ++i) {
            array_[i].~T();
        }

        free(array_);
        size_ = 0;
        capacity_ = 0;
    }

    int insert(const T& value) {
        if (size_ == capacity_) {
            increase_size();
        }

        // copy value to last array cell
        new (array_ + size_) T(value);

        ++size_;
        return size_ - 1;
    }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= size_);

        if (index == size_)
            return insert(value);

        if (size_ == capacity_) {
            increase_size();
        }

        for (int i = size_ - 1; i >= index; --i) {
            new (array_ + i + 1) T(std::move(array_[i]));
            array_[i].~T();
        }

        // copy value to `index` array cell
        new (array_ + index) T(value);
        ++size_;
        return size_ - 1;
    }

    void remove(int index) {
        assert(index >= 0 && index < size_);

        array_[index].~T();
        for (int i = index; i < size_ - 1; ++i) {
            new (array_ + i) T(std::move(array_[i + 1]));
            array_[i + 1].~T();
        }

        --size_;
    }

    int size() const {
        return size_;
    }

    const T& operator[](int index) const {
        return array_[index];
    }

    T& operator[](int index) {
        return array_[index];
    }

    template <typename PointerType>
    struct Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = PointerType;
        using pointer           = value_type*;  // or also value_type*
        using reference         = value_type&;  // or also value_type&

        explicit Iterator(pointer ptr, pointer end) : ptr_(ptr), ptrEnd_(end) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }

        const T& get() const { return *ptr_; }
        void set(const value_type value) { *ptr_ = value; }
        void next() {operator++();}
        bool hasNext() const { return ptr_ < ptrEnd_;}

        // Prefix increment
        Iterator& operator++() { ptr_++; return *this; }
        Iterator& operator--() { ptr_--; return *this; }

        // Postfix increment
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.ptr_ > b.ptr_; };
        friend bool operator>= (const Iterator& a, const Iterator& b) { return a.ptr_ >= b.ptr_; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.ptr_ < b.ptr_; };
        friend bool operator<= (const Iterator& a, const Iterator& b) { return a.ptr_ <= b.ptr_; };

    private:
        pointer ptr_;
        pointer ptrEnd_;

    };

    Iterator<T> begin() { return Iterator<T>(&array_[0], &array_[size_]); }
    Iterator<T> end()   { return Iterator<T>(&array_[size_], &array_[size_]); } // array_ is out of bounds

    Iterator<T> iterator() { return begin(); }
    std::reverse_iterator<Iterator<T>> reverseIteratorBegin() { return std::make_reverse_iterator(end()); }
    std::reverse_iterator<Iterator<T>> reverseIteratorEnd() { return std::make_reverse_iterator(begin()); }

    Iterator<const T> cbegin() const { return Iterator<const T>(&array_[0], &array_[size_]); }
    Iterator<const T> cend() const { return Iterator<const T>(&array_[size_], &array_[size_]); } // array_ is out of bounds

    Iterator<const T> iterator() const { return cbegin(); }
    std::reverse_iterator<Iterator<const T>> reverseIterator() const { return std::make_reverse_iterator(cend()); }

private:
    const float scale_factor_ = 2.0f;
    int capacity_;
    int size_;
    T* array_;

    void increase_size() {
        capacity_ = std::max(capacity_ + 1, (int) (capacity_ * scale_factor_));

        T* new_array = (T*) malloc((capacity_ * sizeof(T)));
        for (int i = 0; i < size_; ++i) {
            new (new_array + i) T(std::move(array_[i]));
        }

        array_ = new_array;
    }
};

#endif //LAB2DYNAMICARRAY_ARRAY_H
