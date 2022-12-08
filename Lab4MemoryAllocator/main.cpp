#include <iostream>
#include "MemoryAllocator/MemoryAllocator.h"

int main() {
    MemoryAllocator allocator;
    allocator.init();

    int *a = (int*) allocator.alloc(sizeof(int));
    int *d = (int*) allocator.alloc(sizeof(int));
    *a = 10;
    *d = 123;

    std::cout << *a << " " << *d << std::endl;

    *a = 34;

    std::cout << *a << " " << *d << std::endl;
    return 0;
}
