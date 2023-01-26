file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalImGui SHARED ${SOURCES})
add_library(Orbital::ImGui ALIAS OrbitalImGui)

target_compile_definitions(OrbitalImGui PUBLIC $<$<CONFIG:Debug>:ORBITAL_IMGUI_DEBUG=1>)
target_include_directories(OrbitalImGui PRIVATE src PUBLIC include)
target_link_libraries(OrbitalImGui PUBLIC glad::glad glfw Orbital::Tools Orbital::Renderer Orbital::Inputs)

# Asset symlink
add_custom_target(OrbitalImGui-ExportAssets ALL)

add_custom_command(TARGET OrbitalImGui-ExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/imgui
  COMMAND_EXPAND_LISTS)

add_dependencies(OrbitalImGui OrbitalImGui-ExportAssets)
add_dependencies(OrbitalImGui-ExportAssets Orbital-CreateAssetDirectory)
