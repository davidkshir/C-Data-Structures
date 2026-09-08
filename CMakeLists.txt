cmake_minimum_required(VERSION 4.3)
project(C_Data_Structures C)

set(CMAKE_C_STANDARD 17)

add_executable(DataStructures
        src/HashTable.c
        src/SLL.c
        src/DLL.c
        src/Stack.c
        src/DyanmicArray.c
        include/DynamicArray.h
)

include_directories(C-Data-Structures PUBLIC include)