file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalEngine SHARED ${SOURCES})
add_library(Orbital::Engine ALIAS OrbitalEngine)

target_precompile_headers(OrbitalEngine PRIVATE include/OrbitalEngine/Context.h)
target_compile_definitions(OrbitalEngine PRIVATE OENGINE_EXPORT)
target_compile_definitions(OrbitalEngine PUBLIC $<$<CONFIG:Debug>:OENGINE_DEBUG=1>)

set(ORBITAL_SCRIPTS_INCLUDE ${PROJECT_SOURCE_DIR}/OrbitalScripts/include PATH)
target_include_directories(OrbitalEngine PUBLIC include ${ORBITAL_SCRIPTS_INCLUDE} PRIVATE src)

target_link_libraries(OrbitalEngine
  PUBLIC Orbital::Tools Orbital::ECS Orbital::Inputs Orbital::Renderer Orbital::Physics)

if(NOT WIN32)
  target_link_libraries(
    OrbitalEngine
    PUBLIC dl)
endif()

# Make assets directory
add_custom_target(Orbital-CreateAssetDirectory ALL)

add_custom_command(TARGET Orbital-CreateAssetDirectory
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
  COMMAND_EXPAND_LISTS)

# Asset symlink
add_custom_target(Orbital-ExportAssets ALL)

add_custom_command(TARGET Orbital-ExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/core
  COMMAND_EXPAND_LISTS)

add_dependencies(Orbital-ExportAssets Orbital-CreateAssetDirectory)
add_dependencies(OrbitalEngine Orbital-ExportAssets)

include(create_game_executable_macro.cmake)
include(create_game_library_macro.cmake)
include(create_game_scripts_macro.cmake)
