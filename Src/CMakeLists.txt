cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled
        ColorImage.cpp
        ColorImage.h
        ColorHistogram.cpp
        ColorHistogram.h
        SimilaritySearch.cpp
)
