file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(Orbital-Scripts SHARED ${SOURCES})
add_library(Orbital::Scripts ALIAS Orbital-Scripts)

target_compile_definitions(Orbital-Scripts PRIVATE ORBITALSCRIPTS_EXPORT)
target_link_libraries(Orbital-Scripts PUBLIC Orbital::Engine)
target_include_directories(Orbital-Scripts PUBLIC include PRIVATE src)

add_custom_command(TARGET Orbital-Scripts POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Orbital-Scripts> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
  COMMAND_EXPAND_LISTS)
