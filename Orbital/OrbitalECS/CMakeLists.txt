file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalECS SHARED ${SOURCES})
add_library(Orbital::ECS ALIAS OrbitalECS)

target_link_libraries(OrbitalECS PUBLIC OrbitalTools)
target_compile_definitions(OrbitalECS PRIVATE OECS_EXPORT)

target_include_directories(OrbitalECS
  PUBLIC include
  PRIVATE src)

# enable_testing() # TODO Better test management

# Unit testing
# add_subdirectory(tests)
