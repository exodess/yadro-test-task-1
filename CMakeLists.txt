cmake_minimum_required(VERSION 3.19)
project(Test_Task1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})