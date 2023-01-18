file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalRenderer SHARED ${SOURCES})
add_library(Orbital::Renderer ALIAS OrbitalRenderer)

target_compile_definitions(OrbitalRenderer PRIVATE ORBITAL_RENDERER_EXPORT)
target_compile_definitions(OrbitalRenderer PUBLIC $<$<CONFIG:Debug>:OBITAL_RENDERER_DEBUG=1>)
target_compile_definitions(OrbitalRenderer PUBLIC ORBITAL_RENDERER_OPENGL)
target_include_directories(OrbitalRenderer PRIVATE src PUBLIC include)
target_link_libraries(OrbitalRenderer PUBLIC glad::glad glfw Orbital::Tools)
