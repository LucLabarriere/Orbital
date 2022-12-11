cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD
    20
)
project(
    OrbitalEngine
    VERSION 0.1.0
)

file(
    GLOB_RECURSE
    SOURCES
    src/*.cpp
)
add_library(
    OrbitalEngine SHARED
    ${SOURCES}
)

target_precompile_headers(
    OrbitalEngine
    PUBLIC 
    include/OrbitalEngine/Context.h
)

target_compile_definitions(
    OrbitalEngine
    PRIVATE OENGINE_EXPORT
)
target_compile_definitions(
    OrbitalEngine
    PUBLIC $<$<CONFIG:Debug>:ODEBUG=1>
)

target_link_libraries(
    OrbitalEngine
    PUBLIC OrbitalECS
           OrbitalInputs
           OrbitalRenderer
           OrbitalPhysics
)

if(NOT WIN32)
    target_link_libraries(
        OrbitalEngine
        PUBLIC dl
    )
endif()

target_include_directories(
    OrbitalEngine
    PUBLIC include ${CMAKE_SOURCE_DIR}/OrbitalScripts/include
    PRIVATE src
)

file(
    GLOB_RECURSE
    ASSET_FILES
    assets/*.*
)
add_custom_target(
    ExportAssets ALL
    DEPENDS ${ASSET_FILES}
)

add_custom_command(
    TARGET ExportAssets
    COMMAND
        ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMAND_EXPAND_LISTS
)
add_dependencies(OrbitalEngine ExportAssets)
