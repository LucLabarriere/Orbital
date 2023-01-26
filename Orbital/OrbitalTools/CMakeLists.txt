file(GLOB_RECURSE SOURCES src/*.cpp)
add_compile_definitions(ORBITAL_DEV)

add_library(OrbitalTools SHARED ${SOURCES})
add_library(Orbital::Tools ALIAS OrbitalTools)

target_precompile_headers(OrbitalTools PUBLIC include/OrbitalTools/Context.h)
target_compile_definitions(OrbitalTools PRIVATE ORBITAL_TOOLS_EXPORT _CRT_SECURE_NO_WARNINGS)
target_link_libraries(OrbitalTools PUBLIC glm::glm nonstd::expected-lite)
target_include_directories(OrbitalTools PUBLIC include PRIVATE src)
