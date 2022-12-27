cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(FPSDemoScripts
  VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(FPSDemoScripts SHARED ${SOURCES})

target_compile_definitions(FPSDemoScripts PRIVATE DEMOSCRIPTS_EXPORT)

target_link_libraries(FPSDemoScripts PUBLIC FPSDemoLibrary)

target_include_directories(FPSDemoScripts
  PUBLIC
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/../FPSDemoLibrary/include
  ${CMAKE_SOURCE_DIR}/OrbitalEngine/include # TODO find a better way to get the include
  PRIVATE
  src)

if (WIN32)
  add_custom_command(TARGET FPSDemoScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:FPSDemoScripts> $<TARGET_FILE_DIR:FPSDemoExecutable>
    COMMAND_EXPAND_LISTS)
else()
  add_custom_command(TARGET FPSDemoScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:FPSDemoScripts> $<TARGET_FILE_DIR:FPSDemoExecutable>
    COMMAND_EXPAND_LISTS)
endif()
