cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(OrbitalTools VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalTools STATIC ${SOURCES})

target_precompile_headers(
    OrbitalTools
    PUBLIC 
    include/OrbitalTools/Context.h
)

target_compile_definitions(OrbitalTools PRIVATE OTOOLS_EXPORT)

target_link_libraries(OrbitalTools PUBLIC glm)

target_include_directories(
    OrbitalTools
    PUBLIC include ${CMAKE_SOURCE_DIR}/vendor/glm/include
    PRIVATE src
)
