cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GTest QUIET)

if(NOT GTest_FOUND)
    message(STATUS "GTest не найден. Загружаю GTest...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        QUIET
    )
    FetchContent_MakeAvailable(googletest)
    message(STATUS "GTest успешно загружен!")
endif()

enable_testing()

add_executable(geometry_tests tests/test_geometry.cpp)
target_link_libraries(geometry_tests PRIVATE
    GTest::gtest_main
    GTest::gtest
)

gtest_discover_tests(geometry_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
