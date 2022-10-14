cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalEngine VERSION 0.1.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(OrbitalEngine SHARED ${SOURCES})

target_compile_definitions(OrbitalEngine PRIVATE OENGINE_EXPORT)
target_link_libraries(OrbitalEngine PUBLIC
    OrbitalECS
    OrbitalInputs
    OrbitalRenderer
)

target_include_directories(OrbitalEngine
	PUBLIC
		include
	PRIVATE
		src
)

# Unit testing
# add_subdirectory(tests)

