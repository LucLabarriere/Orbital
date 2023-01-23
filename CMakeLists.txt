cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)
project(Orbital VERSION 0.3.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_CXX_STANDARD 20) # Make target specific
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(expected-lite CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

set_target_properties(glm::glm PROPERTIES SYSTEM 1)

add_subdirectory(Orbital)
add_subdirectory(Demo)
add_subdirectory(FPSDemo)

