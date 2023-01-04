#message("${CMAKE_CXX_STANDARD}")
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalTools STATIC ${SOURCES})
add_library(Orbital::Tools ALIAS OrbitalTools)

target_precompile_headers(OrbitalTools
  PUBLIC include/OrbitalTools/Context.h)

target_compile_definitions(OrbitalTools PRIVATE OTOOLS_EXPORT)
target_link_libraries(OrbitalTools PUBLIC glm)

target_include_directories(OrbitalTools
  PUBLIC include ${PROJECT_SOURCE_DIR}/../vendor/glm/include # TODO change the vendor folder
  PRIVATE src)
