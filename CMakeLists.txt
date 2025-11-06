cmake_minimum_required(VERSION 3.10)
project(music_player VERSION 0.1.0 LANGUAGES CXX)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/headers)

# Source files (explicit list, no GLOB_RECURSE to avoid picking up temp files)
set(SOURCES
    src/Node.cpp
    src/Playlist.cpp
    src/Song.cpp
    src/main.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})
