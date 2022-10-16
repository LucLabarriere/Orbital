cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalScripts VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalScripts SHARED ${SOURCES})

target_compile_definitions(OrbitalScripts PRIVATE OSCRIPTS_EXPORT)

target_link_libraries(OrbitalScripts PUBLIC OrbitalInputs OrbitalTools OrbitalLogger OrbitalECS OrbitalEngine)

target_include_directories(OrbitalScripts 
	PUBLIC
		include
	PRIVATE
		src
)
