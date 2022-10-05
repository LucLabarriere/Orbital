cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalEditor VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(OrbitalEditor
    ${SOURCES}
)

target_link_libraries(OrbitalEditor PRIVATE
    glad
    glfw 
     OrbitalECS
    OrbitalLogger
    OrbitalRenderer
	# OrbitalScripts
	 OrbitalTools
)

target_include_directories(OrbitalEditor PRIVATE src include
	${CMAKE_SOURCE_DIR}/OrbitalLogger/include/
    ${CMAKE_SOURCE_DIR}/OrbitalRenderer/include/
)

if (WIN32)
add_custom_command(TARGET OrbitalEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:OrbitalEditor> $<TARGET_FILE_DIR:OrbitalEditor>
    COMMAND_EXPAND_LISTS
)
ENDIF()

