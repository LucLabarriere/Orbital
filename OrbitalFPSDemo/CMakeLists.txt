cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)

project(FPSDemo VERSION 0.1.0)

add_subdirectory(FPSDemoLibrary)
add_subdirectory(FPSDemoScripts)
add_subdirectory(FPSDemo)
