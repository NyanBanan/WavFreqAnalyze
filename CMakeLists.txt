cmake_minimum_required(VERSION 3.27)
project(WaveAnalyse)

set(CMAKE_CXX_STANDARD 20)

add_executable(WaveAnalyse main.cpp
        wav/WavData.cpp
        wav/WavData.hpp
        wav/chunk/Chunk.cpp
        wav/chunk/Chunk.hpp
        wav/chunk/RiffChunk.cpp
        wav/chunk/RiffChunk.hpp
        wav/chunk/FmtChunk.cpp
        wav/chunk/FmtChunk.hpp
        wav/chunk/DataChunk.cpp
        wav/chunk/DataChunk.hpp)
