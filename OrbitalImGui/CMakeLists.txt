file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(OrbitalImGui SHARED ${SOURCES})
add_library(Orbital::ImGui ALIAS OrbitalImGui)

#target_precompile_headers(OrbitalImGui PRIVATE include/OrbitalImGui/Context.h)
target_compile_definitions(OrbitalImGui PRIVATE OIMGUI_EXPORT)
target_compile_definitions(OrbitalImGui PUBLIC $<$<CONFIG:Debug>:OIMGUI_DEBUG=1>)

target_include_directories(OrbitalImGui PRIVATE src PUBLIC include)
