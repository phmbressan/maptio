cmake_minimum_required(VERSION 3.10)
project(maptio)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(maptio
    src/interpolation.cpp
    src/extrapolation.cpp
)

add_executable(maptio_main src/main.cpp)
target_link_libraries(maptio_main maptio)

enable_testing()

add_subdirectory(tests)