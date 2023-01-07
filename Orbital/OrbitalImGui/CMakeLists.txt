add_library(OrbitalImGui SHARED
  src/imgui.cpp
  src/imgui_draw.cpp
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui_tables.cpp
  src/imgui_demo.cpp
  src/imgui_widgets.cpp)

add_library(Orbital::ImGui ALIAS OrbitalImGui)

#target_precompile_headers(OrbitalImGui PRIVATE include/OrbitalImGui/Context.h)
target_compile_definitions(OrbitalImGui PRIVATE OIMGUI_EXPORT)
target_compile_definitions(OrbitalImGui PUBLIC $<$<CONFIG:Debug>:OIMGUI_DEBUG=1>)
target_include_directories(OrbitalImGui PRIVATE src PUBLIC include)
target_link_libraries(OrbitalImGui PUBLIC glfw)

add_executable(ImGuiDemo
  src/main.cpp)

#target_include_directories(ImGuiDemo PRIVATE
#  ${PROJECT_SOURCE_DIR}/../vendor/glad/include)

if(NOT WIN32)
  target_link_libraries(
	  ImGuiDemo 
    PUBLIC dl)
endif()

target_link_libraries(ImGuiDemo PUBLIC OrbitalImGui OrbitalRenderer)
