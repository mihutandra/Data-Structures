cmake_minimum_required(VERSION 3.24)

project(MultiMap)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        MultiMap.h MultiMap.cpp
        MultiMapIterator.h MultiMapIterator.cpp
        ShortTest.h ShortTest.cpp
        ExtendedTest.h ExtendedTest.cpp
        App.cpp)