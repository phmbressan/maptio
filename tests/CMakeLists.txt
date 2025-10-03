find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tests/utils
)


file(GLOB TEST_SOURCES "unit/*.cpp")

add_executable(test_maptio ${TEST_SOURCES})

target_link_libraries(test_maptio
    maptio_core
    gtest_main
    ${GTEST_LIBRARIES}
    pthread
)
target_include_directories(test_maptio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME test_maptio COMMAND test_maptio)