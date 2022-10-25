cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD
    20
)
project(
    OrbitalPhysics
    VERSION 0.1.0
)

file(
    GLOB_RECURSE
    SOURCES
    src/*.cpp
)
add_library(
    OrbitalPhysics SHARED
    ${SOURCES}
)

target_link_libraries(
    OrbitalPhysics
    PUBLIC OrbitalTools OrbitalECS
)
target_compile_definitions(
    OrbitalPhysics
    PRIVATE OPHYSICS_EXPORT
)

target_include_directories(
    OrbitalPhysics
    PUBLIC include
           ${CMAKE_SOURCE_DIR}/OrbitalTools/include
           ${CMAKE_SOURCE_DIR}/OrbitalLogger/include
    PRIVATE src
)
