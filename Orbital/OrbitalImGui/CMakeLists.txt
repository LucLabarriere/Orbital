add_library(OrbitalImGui STATIC
  src/core/imgui.cpp
  src/core/imgui_draw.cpp
  src/core/imgui_impl_glfw.cpp
  src/core/imgui_impl_opengl3.cpp
  src/core/imgui_tables.cpp
  src/core/imgui_demo.cpp
  src/core/imgui_widgets.cpp
  src/DebugLayer.cpp)

add_library(Orbital::ImGui ALIAS OrbitalImGui)

#target_precompile_headers(OrbitalImGui PRIVATE include/OrbitalImGui/Context.h)
#target_compile_definitions(OrbitalImGui PRIVATE OIMGUI_EXPORT)
target_compile_definitions(OrbitalImGui PUBLIC $<$<CONFIG:Debug>:OIMGUI_DEBUG=1>)
target_include_directories(OrbitalImGui
  PRIVATE src
  PUBLIC include
  ${PROJECT_SOURCE_DIR}/../vendor/glfw/include
  ${PROJECT_SOURCE_DIR}/../vendor/glad/include
  ${PROJECT_SOURCE_DIR}/../vendor/glm
  ${PROJECT_SOURCE_DIR}/OrbitalRenderer/include
  ${PROJECT_SOURCE_DIR}/OrbitalEngine/include
  ${PROJECT_SOURCE_DIR}/OrbitalInputs/include
  ${PROJECT_SOURCE_DIR}/OrbitalTools/include)

# Asset symlink
add_custom_target(OrbitalImGui-ExportAssets ALL)

add_custom_command(TARGET OrbitalImGui-ExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/imgui
  COMMAND_EXPAND_LISTS)

add_dependencies(OrbitalImGui OrbitalImGui-ExportAssets)
add_dependencies(OrbitalImGui-ExportAssets Orbital-CreateAssetDirectory)

#target_link_libraries(OrbitalImGui PUBLIC Orbital::Engine)

if (${ORBITAL_IMGUI_DEMO})
  add_executable(ImGuiDemo
    src/demos/orbital_example.cpp)
  if(NOT WIN32)
    target_link_libraries(
      ImGuiDemo
      PUBLIC dl)
  endif()
  target_link_libraries(ImGuiDemo PUBLIC OrbitalImGui OrbitalRenderer)
endif()

if (${ORBITAL_IMGUI_GLFWEXAMPLE})
  find_package(OpenGL)
  add_executable(ImGuiGLFWExample
    src/demos/glfw_example.cpp)
  target_link_libraries(ImGuiGLFWExample PUBLIC OrbitalImGui glfw opengl32)
endif ()
