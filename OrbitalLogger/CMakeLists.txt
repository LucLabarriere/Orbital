cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalLogger VERSION 0.1.0)

add_library(OrbitalLogger SHARED
    src/Logger.cpp
)

target_compile_definitions(OrbitalLogger PRIVATE OLOGGER_EXPORT)
target_compile_definitions(OrbitalLogger PRIVATE
    $<$<CONFIG:Debug>:OLOGGER_DEBUG=1>
)
target_include_directories(OrbitalLogger PUBLIC include PRIVATE src)
