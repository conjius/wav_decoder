cmake_minimum_required(VERSION 3.28)
project(wav_decoder)

set(CMAKE_CXX_STANDARD 20)

add_executable(wav_decoder
		src/main.cpp
		src/ByteUtils.hpp
		src/FileReader.cpp
		src/FileReader.hpp
		src/FileReaderReadResult.hpp
		src/fx/FxProcessor.cpp
		src/fx/FxProcessor.hpp
		src/fx/FxProcessorInput.hpp
		src/Converter.h
)
