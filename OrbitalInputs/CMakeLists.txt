cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalInputs VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalInputs SHARED ${SOURCES})

target_compile_definitions(OrbitalInputs PRIVATE OINPUTS_EXPORT)
target_compile_definitions(OrbitalRenderer PRIVATE OINPUTS_OPENGL)
target_link_libraries(OrbitalInputs PRIVATE glfw OrbitalLogger)

target_include_directories(OrbitalInputs 
	PUBLIC
		include
	PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include
		src
)
