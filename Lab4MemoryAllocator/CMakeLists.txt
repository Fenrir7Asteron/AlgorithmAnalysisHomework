cmake_minimum_required(VERSION 3.22)
project(Lab4MemoryAllocator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab4MemoryAllocator main.cpp
        MemoryAllocator/MemoryAllocator.cpp MemoryAllocator/MemoryAllocator.h
        MemoryAllocator/FSA/FSA.cpp MemoryAllocator/FSA/FSA.h MemoryAllocator/FSA/FSAPage.cpp MemoryAllocator/FSA/FSAPage.h
        MemoryAllocator/FSA/FSABlockMetaData.h MemoryAllocator/MemoryAllocatorConstants.h
        MemoryAllocator/CommonBlockMetaData.cpp MemoryAllocator/CommonBlockMetaData.h
        MemoryAllocator/CoalesceAllocator/CoalesceAllocator.cpp MemoryAllocator/CoalesceAllocator/CoalesceAllocator.h
        MemoryAllocator/IMemoryPage.h MemoryAllocator/CoalesceAllocator/CoalescePage.cpp MemoryAllocator/CoalesceAllocator/CoalescePage.h MemoryAllocator/CoalesceAllocator/CoalesceBlockMetaData.h MemoryAllocator/OccupiedBlock.h)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(" ")
    message("CMAKE IN DEBUG MODE")
    message(" ")
    add_compile_definitions(DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(" ")
    message("CMAKE IN RELEASE MODE")
    message(" ")
    add_compile_definitions(NDEBUG)
endif ()