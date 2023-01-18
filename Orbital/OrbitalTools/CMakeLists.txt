#message("${CMAKE_CXX_STANDARD}")
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalTools STATIC ${SOURCES})
add_library(Orbital::Tools ALIAS OrbitalTools)

target_precompile_headers(OrbitalTools PUBLIC include/OrbitalTools/Context.h)
target_compile_definitions(OrbitalTools PRIVATE ORBITAL_TOOLS_EXPORT)
target_link_libraries(OrbitalTools PUBLIC glm::glm)

target_include_directories(OrbitalTools PUBLIC include PRIVATE src)
