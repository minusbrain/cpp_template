cmake_minimum_required (VERSION 3.12)

# Name of the project
project (template VERSION 0.1)
enable_testing()

#find_package(ZLIB REQUIRED)
#find_package(Boost 1.58 REQUIRED ALL)
find_package(GTest REQUIRED CONFIG)
SET(GTEST_LIBS_TO_LINK GTest::gtest GTest::gmock GTest::gmock_main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(ext/aelib)
include_directories(src)

cmake_policy(SET CMP0076 NEW) # https://cmake.org/cmake/help/latest/policy/CMP0076.html

add_subdirectory(doc)
add_subdirectory(ext)
add_subdirectory(src)
