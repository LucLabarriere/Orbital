cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalEngine VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(OrbitalEngine SHARED ${SOURCES})

target_precompile_headers(OrbitalEngine
  PUBLIC
  include/OrbitalEngine/Context.h)

target_compile_definitions(OrbitalEngine
  PRIVATE
  OENGINE_EXPORT)
 
target_compile_definitions(OrbitalEngine
  PUBLIC
  $<$<CONFIG:Debug>:OENGINE_DEBUG=1>)

target_link_libraries(OrbitalEngine
  PUBLIC
  OrbitalTools
  OrbitalECS
  OrbitalInputs
  OrbitalRenderer
  OrbitalPhysics)

if(NOT WIN32)
  target_link_libraries(
    OrbitalEngine
    PUBLIC dl)
endif()

target_include_directories(OrbitalEngine
  PUBLIC
  include

  PRIVATE
  src)

# Make assets directory
add_custom_target(
	${PROJECT_NAME}CreateAssetDirectory ALL)

add_custom_command(
	TARGET ${PROJECT_NAME}CreateAssetDirectory
  COMMAND
  ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
  COMMAND_EXPAND_LISTS)

# Asset symlink
file(
  GLOB_RECURSE
  ASSET_FILES
  assets/*.*)

add_custom_target(
  ${PROJECT_NAME}ExportAssets ALL
  DEPENDS ${ASSET_FILES})

add_custom_command(
  TARGET ${PROJECT_NAME}ExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/core/
  COMMAND_EXPAND_LISTS)

add_dependencies(${PROJECT_NAME}ExportAssets ${PROJECT_NAME}CreateAssetDirectory)

# Macro to create a Game Executable CMakeLists.txt
include(create_game_executable_macro.cmake)
include(create_game_library_macro.cmake)
include(create_game_scripts_macro.cmake)
