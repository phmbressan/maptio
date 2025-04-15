cmake_minimum_required(VERSION 3.10)
project(maptio)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(maptio ${MAPTIO_SOURCES})

target_include_directories(maptio
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

add_executable(maptio_main src/main.cpp)
target_link_libraries(maptio PUBLIC Eigen3::Eigen)
target_link_libraries(maptio_main maptio)

enable_testing()
add_subdirectory(tests)
