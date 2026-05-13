cmake_minimum_required(VERSION 3.19)
project(Task1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB src_files "src/*.cpp")
file(GLOB test_files "tests/*.cpp")
file(GLOB txt_files "tests/*.txt")

file(COPY ${txt_files}
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(${PROJECT_NAME} ${src_files})
add_compile_definitions(${PROJECT_NAME} DEBUG)

# тестирование с помощью GoogleTest
find_package(GTest REQUIRED)
include(GoogleTest)

enable_testing() # чтобы можно было запускать через ctest

add_executable(${PROJECT_NAME}_Test ${src_files} ${test_files})
target_link_libraries(${PROJECT_NAME}_Test PRIVATE
        GTest::gtest_main
)

gtest_discover_tests(${PROJECT_NAME}_Test)