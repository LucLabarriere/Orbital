
cmake_minimum_required(VERSION 3.16.0)
cmake_policy(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalRenderer VERSION 0.1.0)

add_library(OrbitalRenderer SHARED
    src/Window.cpp
)

target_compile_definitions(OrbitalRenderer PRIVATE OLOGGER_EXPORT)

target_link_libraries(OrbitalRenderer PRIVATE
    glad
    glfw
)
 
target_include_directories(OrbitalRenderer PUBLIC src include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/OrbitalLogger/include
)
