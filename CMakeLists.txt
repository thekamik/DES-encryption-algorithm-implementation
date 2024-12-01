cmake_minimum_required(VERSION 3.10)  # Specify CMake version
project(Crypto VERSION 1.1 LANGUAGES CXX)  # Project name and version

set(CMAKE_CXX_STANDARD 23)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/DES/include
)

# Add executable
add_executable(main
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/DES/src/DES_functions.cpp
)