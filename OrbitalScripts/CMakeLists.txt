cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(OrbitalScripts VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalScripts SHARED ${SOURCES})

target_compile_definitions(OrbitalScripts PRIVATE OSCRIPTS_EXPORT)

target_link_libraries(OrbitalScripts PUBLIC OrbitalInputs OrbitalTools OrbitalECS OrbitalEngine)

target_include_directories(OrbitalScripts 
	PUBLIC
		include
	PRIVATE
		src
)

if (WIN32)
    add_custom_command(TARGET OrbitalScripts POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:OrbitalScripts> $<TARGET_FILE_DIR:OrbitalEditor>
        COMMAND_EXPAND_LISTS
)
else()
    add_custom_command(TARGET OrbitalScripts POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:OrbitalScripts> $<TARGET_FILE_DIR:OrbitalEditor>
        COMMAND_EXPAND_LISTS
)
endif()
