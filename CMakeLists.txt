cmake_minimum_required(VERSION 3.16)
project(jieqiai)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(./engine)
add_subdirectory(./server)
