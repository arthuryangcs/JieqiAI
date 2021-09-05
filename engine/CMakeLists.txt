cmake_minimum_required(VERSION 3.16)
project(eleeye)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(eleeye.exe ../base/pipe.cpp ucci.cpp pregen.cpp position.cpp genmoves.cpp hash.cpp book.cpp movesort.cpp preeval.cpp evaluate.cpp search.cpp eleeye.cpp)
