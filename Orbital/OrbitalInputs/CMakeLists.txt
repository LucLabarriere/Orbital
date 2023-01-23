file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalInputs SHARED ${SOURCES})
add_library(Orbital::Inputs ALIAS OrbitalInputs)

target_compile_definitions(OrbitalInputs PRIVATE ORBITAL_INPUTS_EXPORT)
# TODO move following compile definition, it should be the user's choice
target_compile_definitions(OrbitalInputs PUBLIC OINPUTS_GLFW)
target_link_libraries(OrbitalInputs PUBLIC Orbital::Tools PRIVATE glfw)


target_include_directories(OrbitalInputs
  PUBLIC include
  PRIVATE src ${CMAKE_SOURCE_DIR}/vendor/glfw/include)
