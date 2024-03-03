cmake_minimum_required(VERSION 3.24)

project(maplabstruct)

set(CMAKE_CXX_STANDARD 23)

add_executable(App.cpp Map.cpp MapIterator.cpp ShortTest.cpp ExtendedTest.cpp
                ExtendedTest.h Map.h MapIterator.h ShortTest.h App.cpp)
