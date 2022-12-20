cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(DemoScripts
  VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(DemoScripts SHARED ${SOURCES})

target_compile_definitions(DemoScripts PRIVATE DEMOSCRIPTS_EXPORT)

target_link_libraries(DemoScripts PUBLIC DemoLibrary)

target_include_directories(DemoScripts
  PUBLIC
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/../DemoLibrary/include
  ${CMAKE_SOURCE_DIR}/OrbitalEngine/include # TODO find a better way to get the include
  PRIVATE
  src)

if (WIN32)
  add_custom_command(TARGET DemoScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DemoScripts> $<TARGET_FILE_DIR:DemoExecutable>
    COMMAND_EXPAND_LISTS)
else()
  add_custom_command(TARGET DemoScripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:DemoScripts> $<TARGET_FILE_DIR:DemoExecutable>
    COMMAND_EXPAND_LISTS)
endif()
