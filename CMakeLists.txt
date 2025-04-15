cmake_minimum_required(VERSION 3.10)
project(maptio)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(maptio ${MAPTIO_SOURCES})

add_executable(maptio_main src/main.cpp)
target_link_libraries(maptio_main maptio)

enable_testing()

add_subdirectory(tests)