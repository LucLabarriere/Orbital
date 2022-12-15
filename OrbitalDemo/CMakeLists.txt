cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(OrbitalDemo VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(OrbitalDemo
    ${SOURCES}
)

target_link_libraries(OrbitalDemo PRIVATE
    OrbitalEngine
)

target_include_directories(OrbitalDemo PRIVATE src include)

if (WIN32)
    add_custom_command(TARGET OrbitalDemo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:OrbitalDemo> $<TARGET_FILE_DIR:OrbitalDemo>
        COMMAND_EXPAND_LISTS
    )
else()
    add_custom_command(TARGET OrbitalDemo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:OrbitalScripts> $<TARGET_FILE_DIR:OrbitalDemo>
        COMMAND_EXPAND_LISTS
    )
endif()

add_dependencies(OrbitalDemo OrbitalScripts)
