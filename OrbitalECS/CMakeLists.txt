cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalECS VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalECS SHARED ${SOURCES})

target_link_libraries(OrbitalECS PUBLIC OrbitalTools)
target_compile_definitions(OrbitalECS PRIVATE OECS_EXPORT)

target_include_directories(OrbitalECS
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/OrbitalTools/include
        ${CMAKE_SOURCE_DIR}/OrbitalLogger/include
	PRIVATE
		src
)

# Unit testing
add_subdirectory(tests)

