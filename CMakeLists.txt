# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Declare project
project(BabaIsAgent)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# External libraries
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(Libraries/googletest)

cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(SFML_BUILD_AUDIO FALSE)
add_subdirectory(Libraries/SFML)

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(Libraries/spdlog)
add_subdirectory(Libraries/pybind11)

# Includes
include_directories(Includes)
include_directories(Libraries/SFML/include)
include_directories(Libraries/pybind11/include)
include_directories(Libraries/random/include)

# Compile options
include(CMake/CompileOptions.cmake)

# Project modules
add_subdirectory(Sources/Baba)
add_subdirectory(UnitTest)

add_subdirectory(Extension/BabaGUI)
add_subdirectory(Extension/pyBaba)

# Code coverage
option(BUILD_COVERAGE "Build code coverage" OFF)
if(CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CMake/CodeCoverage.cmake)
    setup_target_for_coverage(${PROJECT_NAME}_coverage UnitTest coverage)
endif()
