cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(TestProject VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(TestProject
    ${SOURCES}
)

target_include_directories(TestProject PRIVATE src include)
