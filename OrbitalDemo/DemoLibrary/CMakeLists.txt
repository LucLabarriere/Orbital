cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(DemoLibrary
  VERSION 0.1.0
)

file(
  GLOB_RECURSE
  SOURCES
  src/*.cpp)

add_library(
  DemoLibrary SHARED
  ${SOURCES})

target_precompile_headers(
  DemoLibrary
  PUBLIC
  include/DemoLibrary/Context.h)

target_compile_definitions(
  DemoLibrary
  PUBLIC $<$<CONFIG:Debug>:ODEBUG=1>
  PRIVATE DEMOLIB_EXPORT)

target_link_libraries(
  DemoLibrary
  PUBLIC OrbitalEngine)

if(NOT WIN32)
  target_link_libraries(
    DemoLibrary
    PUBLIC dl)
endif()

target_include_directories(
  DemoLibrary
  PUBLIC include ${CMAKE_CURRENT_SOURCE_DIR}/../DemoScripts/include
  PRIVATE src)

file(
  GLOB_RECURSE
  ASSET_FILES
  assets/*.*)
add_custom_target(
  DemoExportAssets ALL
  DEPENDS ${ASSET_FILES})

add_custom_command(
  TARGET DemoExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
  COMMAND_EXPAND_LISTS)

add_dependencies(DemoLibrary DemoExportAssets)
