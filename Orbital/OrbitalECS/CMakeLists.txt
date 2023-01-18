file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalECS SHARED ${SOURCES})
add_library(Orbital::ECS ALIAS OrbitalECS)

target_compile_definitions(OrbitalECS PUBLIC $<$<CONFIG:Debug>:ORBITAL_ECS_DEBUG=1>)
target_compile_definitions(OrbitalECS PRIVATE ORBITAL_ECS_EXPORT)
target_include_directories(OrbitalECS PUBLIC include PRIVATE src)
target_link_libraries(OrbitalECS PUBLIC Orbital::Tools)
