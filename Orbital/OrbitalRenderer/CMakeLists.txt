file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalRenderer SHARED ${SOURCES})
add_library(Orbital::Renderer ALIAS OrbitalRenderer)

#target_precompile_headers(OrbitalRenderer PRIVATE include/OrbitalRenderer/Context.h)

target_compile_definitions(OrbitalRenderer PRIVATE ORENDERER_EXPORT)
# TODO the following compile definition should be set elsewhere (defined by the user)
target_compile_definitions(OrbitalRenderer PRIVATE ORENDERER_OPENGL)
target_compile_definitions(OrbitalRenderer PRIVATE $<$<CONFIG:Debug>:ORENDERER_DEBUG=1>)

target_link_libraries(OrbitalRenderer PUBLIC glad glfw Orbital::Tools)

target_include_directories(OrbitalRenderer
  PRIVATE
  src
  PUBLIC
  ${PROJECT_SOURCE_DIR}/../vendor/glad/include
  ${PROJECT_SOURCE_DIR}/../vendor/glfw/include
  include)
