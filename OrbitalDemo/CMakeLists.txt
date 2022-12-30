cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(Demo VERSION 0.1.0)

add_subdirectory(DemoLibrary)
add_subdirectory(DemoScripts)
add_subdirectory(Demo)
