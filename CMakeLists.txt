cmake_minimum_required(VERSION 3.10)
project(music_player VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/headers)

# Collect source files (src/ and top-level .cpp)
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/*.cpp
)

add_executable(music_player ${SRC_FILES})
