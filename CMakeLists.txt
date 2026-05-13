cmake_minimum_required(VERSION 3.19)
project(Task1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB src_files "src/*.cpp")
file(GLOB test_files "tests/*.cpp")

add_library(Task1 ${src_files})

# тестирование с помощью GoogleTest
find_package(GTest REQUIRED)
include(GoogleTest)

enable_testing() # чтобы можно было запускать через ctest

add_executable(${PROJECT_NAME}_Test ${test_files})
target_link_libraries(${PROJECT_NAME}_Test PRIVATE
        ${PROJECT_NAME}
        GTest::gtest_main
)

gtest_discover_tests(${PROJECT_NAME}_Test)