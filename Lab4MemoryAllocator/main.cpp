#include <iostream>
#include "MemoryAllocator/MemoryAllocator.h"

int main() {
    MemoryAllocator allocator;
    allocator.init();

    int *a = (int*) allocator.alloc(sizeof(int));
    int *d = (int*) allocator.alloc(sizeof(int));
    std::string ch = (char*) allocator.alloc(100);
    *a = 10;
    *d = 123;
    ch = "dfjsdfoisjoiefjoiesfjseiofj";

    std::cout << sizeof(FSAPage) << std::endl;
    std::cout << *a << " " << *d << " " << ch << std::endl;

    *a = 34;

    std::cout << *a << " " << *d << std::endl;

    allocator.free(a);

    std::cout << *d << std::endl;

    a = (int*) allocator.alloc(sizeof(int));
    *a = 5;

    std::cout << *a << " " << *d << std::endl;

    for (int i = 0; i < 2050; ++i) {
        allocator.alloc(512);
    }

    allocator.free(d);

    allocator.alloc(sizeof(char));

    allocator.destroy();

    return 0;
}
