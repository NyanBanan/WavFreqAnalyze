cmake_minimum_required(VERSION 3.27)
project(WaveAnalyse)

set(CMAKE_CXX_STANDARD 23)

add_executable(WaveAnalyse main.cpp
        wav/chunk/Chunk.cpp
        wav/chunk/Chunk.hpp
        wav/chunk/RIFFChunk.cpp
        wav/chunk/RIFFChunk.hpp
        wav/chunk/FmtChunk.cpp
        wav/chunk/FmtChunk.hpp
        wav/chunk/DataChunk.cpp
        wav/chunk/DataChunk.hpp
        wav/WavParser.hpp)
