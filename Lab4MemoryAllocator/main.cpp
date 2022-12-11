#include <iostream>
#include "MemoryAllocator/MemoryAllocator.h"

int main() {
    MemoryAllocator allocator;
    allocator.init();

//    int *a = (int*) allocator.alloc(sizeof(int));
//    int *d = (int*) allocator.alloc(sizeof(int));
//    std::string ch = (char*) allocator.alloc(100);
//    *a = 10;
//    *d = 123;
//    ch = "dfjsdfoisjoiefjoiesfjseiofj";
//
//    std::cout << sizeof(bool) << std::endl;
//    std::cout << *a << " " << *d << " " << ch << std::endl;
//
//    *a = 34;
//
//    std::cout << *a << " " << *d << std::endl;
//
//    allocator.free(a);
//
//    std::cout << *d << std::endl;
//
//    a = (int*) allocator.alloc(sizeof(int));
//    *a = 5;
//
//    std::cout << *a << " " << *d << std::endl;
//
//    for (int i = 0; i < 2050; ++i) {
//        allocator.alloc(512);
//    }
//
//    allocator.free(d);
//
//    allocator.alloc(sizeof(char));

    int *pa = (int *)allocator.alloc(1024 * sizeof(int));
    pa[0] = 25;
    pa[1] = 50;
    std::cout << pa[0] << " " << pa[1] << std::endl;

    int *pa2 = (int *)allocator.alloc(1024 * sizeof(int));
    pa2[0] = 123;
    pa2[1] = 234;

    allocator.alloc(1024 * sizeof(int));

    allocator.free(pa);
    allocator.alloc(2000 * sizeof(int));

    allocator.free(pa2);

    allocator.destroy();

    return 0;
}
