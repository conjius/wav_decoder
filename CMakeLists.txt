cmake_minimum_required(VERSION 3.28)
project(wav_decoder)

set(CMAKE_CXX_STANDARD 20)

add_executable(wav_decoder
		src/main.cpp
		src/ByteUtils.h
		src/FileReader.cpp
		src/FileReader.h
)
