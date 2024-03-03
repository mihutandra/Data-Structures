cmake_minimum_required(VERSION 3.24)
project(PriorityQueue)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PriorityQueue
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h)
