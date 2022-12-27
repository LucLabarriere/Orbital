cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(FPSDemoLibrary
  VERSION 0.1.0
)

file(
  GLOB_RECURSE
  SOURCES
  src/*.cpp)

add_library(
  FPSDemoLibrary SHARED
  ${SOURCES})

target_precompile_headers(
  FPSDemoLibrary
  PUBLIC
  include/FPSDemoLibrary/Context.h)

target_compile_definitions(
  FPSDemoLibrary
  PUBLIC $<$<CONFIG:Debug>:ODEBUG=1>
  PRIVATE DEMOLIB_EXPORT)

target_link_libraries(
  FPSDemoLibrary
  PUBLIC OrbitalEngine)

if(NOT WIN32)
  target_link_libraries(
    FPSDemoLibrary
    PUBLIC dl)
endif()

target_include_directories(
  FPSDemoLibrary
  PUBLIC include ${CMAKE_CURRENT_SOURCE_DIR}/../FPSDemoScripts/include ${CMAKE_CURRENT_SOURCE_DIR}/../../OrbitalScripts/include
  PRIVATE src)

file(
  GLOB_RECURSE
  ASSET_FILES
  assets/*.*)
add_custom_target(
  FPSDemoExportAssets ALL
  DEPENDS ${ASSET_FILES})

add_custom_command(
  TARGET FPSDemoExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
  COMMAND_EXPAND_LISTS)

add_dependencies(FPSDemoLibrary FPSDemoExportAssets)
