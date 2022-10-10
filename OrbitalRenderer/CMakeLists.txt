
cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalRenderer VERSION 0.1.0)
file (GLOB_RECURSE SOURCES src/*.cpp)

add_library(OrbitalRenderer SHARED
    ${SOURCES}
)

target_compile_definitions(OrbitalRenderer PRIVATE ORENDERER_EXPORT)
target_compile_definitions(OrbitalRenderer PRIVATE ORENDERER_OPENGL)
target_compile_definitions(OrbitalRenderer PRIVATE
    $<$<CONFIG:Debug>:ORENDERER_DEBUG=1>
)

target_link_libraries(OrbitalRenderer PRIVATE glad glfw)

target_include_directories(OrbitalRenderer
    PRIVATE
        src
    PUBLIC
        include
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include
        ${CMAKE_SOURCE_DIR}/OrbitalLogger/include
)
