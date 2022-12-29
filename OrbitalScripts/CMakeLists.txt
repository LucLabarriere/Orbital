cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalScripts
  VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalScripts SHARED ${SOURCES})

target_compile_definitions(OrbitalScripts PRIVATE ORBITALSCRIPTS_EXPORT)
target_link_libraries(OrbitalScripts PUBLIC OrbitalEngine)

target_include_directories(OrbitalScripts
  PUBLIC
  include
  ${CMAKE_SOURCE_DIR}/OrbitalEngine/include # TODO find a better way to get the include
  PRIVATE
  src)

if (WIN32)
  add_custom_command(TARGET OrbitalScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:OrbitalScripts> ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
    COMMAND_EXPAND_LISTS)
else()
  add_custom_command(TARGET OrbitalScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:OrbitalScripts> ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
    COMMAND_EXPAND_LISTS)
endif()
