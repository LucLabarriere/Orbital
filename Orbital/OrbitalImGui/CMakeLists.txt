add_library(OrbitalImGui STATIC
  src/imgui.cpp
  src/imgui_draw.cpp
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui_tables.cpp
  src/imgui_demo.cpp
  src/imgui_widgets.cpp)

add_library(Orbital::ImGui ALIAS OrbitalImGui)

#target_precompile_headers(OrbitalImGui PRIVATE include/OrbitalImGui/Context.h)
#target_compile_definitions(OrbitalImGui PRIVATE OIMGUI_EXPORT)
target_compile_definitions(OrbitalImGui PUBLIC $<$<CONFIG:Debug>:OIMGUI_DEBUG=1>)
target_include_directories(OrbitalImGui
  PRIVATE src
  PUBLIC include ${PROJECT_SOURCE_DIR}/../vendor/glfw/include)

add_executable(ImGuiDemo
  src/main.cpp)

if(NOT WIN32)
  target_link_libraries(
    ImGuiDemo
    PUBLIC dl)
endif()

target_link_libraries(ImGuiDemo PUBLIC OrbitalImGui OrbitalRenderer)

if (${ORBITAL_IMGUI_GLFWEXAMPLE})
  add_executable(ImGuiGLFWExample
    src/glfw_example.cpp)
  find_package(OpenGL)
  target_link_libraries(ImGuiGLFWExample PUBLIC OrbitalImGui glfw opengl32)
endif ()
