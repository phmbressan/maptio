cmake_minimum_required(VERSION 3.15...3.27)
project(maptio)

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python 3.8 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)

# Source files for core library
file(GLOB_RECURSE MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MAPTIO_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Source file for the Python bindings
file(GLOB_RECURSE MAPTIO_BIND ${PROJECT_SOURCE_DIR}/bindings/bindings.cpp)

# Core C++ library compilation
add_library(maptio_core ${MAPTIO_SOURCES})
set_property(TARGET maptio_core PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(maptio_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Main executable for quick testing
add_executable(maptio_main src/main.cpp)
target_link_libraries(maptio_main PRIVATE maptio_core)

# Python module
nanobind_add_module(maptio STABLE_ABI NB_STATIC NOMINSIZE ${MAPTIO_BIND})
# Link the Python module against your core C++ library
target_link_libraries(maptio PRIVATE maptio_core)

# Install the Python module
install(TARGETS maptio LIBRARY DESTINATION .)

# Testing
enable_testing()
add_subdirectory(tests)