cmake_minimum_required(VERSION 3.27)
project(WaveAnalyse)

set(CMAKE_CXX_STANDARD 20)

add_executable(WaveAnalyse main.cpp
        wav/chunk/Chunk.cpp
        wav/chunk/Chunk.hpp)
