file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalPhysics SHARED ${SOURCES})
add_library(Orbital::Physics ALIAS OrbitalPhysics)

target_link_libraries(OrbitalPhysics PUBLIC Orbital::Tools)
target_compile_definitions(OrbitalPhysics PRIVATE ORBITAL_PHYSICS_EXPORT)
target_compile_definitions(OrbitalPhysics PUBLIC $<$<CONFIG:Debug>:ODEBUG=1>)
#target_precompile_headers(OrbitalPhysics PRIVATE include/OrbitalPhysics/Context.h)

target_include_directories(
  OrbitalPhysics
  PUBLIC include
  PRIVATE src)

#enable_testing()

# Unit testing
#add_subdirectory(tests)
