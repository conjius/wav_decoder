cmake_minimum_required(VERSION 3.29.2)
set(PROJECT_NAME wav_decoder)
set(CMAKE_PREFIX_PATH "/opt/homebrew/lib/cmake/${CMAKE_PREFIX_PATH}")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
		src/main.cpp
		src/ByteUtils.hpp
		src/FileReader.cpp
		src/FileReader.hpp
		src/FileReaderReadResult.hpp
		src/Converter.hpp
		src/StringUtils.hpp

		src/fx/FxProcessor.cpp
		src/fx/FxProcessor.hpp
		src/fx/FxProcessorInput.hpp
		src/fx/Effect.hpp
		src/fx/EffectBuilder.hpp

		src/cli/CliArgParser.cpp
		src/cli/CliArgParser.hpp
		src/fx/EffectBuilder.cpp
		src/player/AudioPlayer.cpp
		src/player/AudioPlayer.h
)

# Find required packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

# Find RtAudio via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RtAudio REQUIRED IMPORTED_TARGET rtaudio)

# Include directories
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog fmt::fmt CLI11::CLI11 PkgConfig::RtAudio)
