cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(OrbitalTools VERSION 0.1.0)

add_library(OrbitalTools SHARED
src/Context.cpp
include/OrbitalTools/Context.h
include/OrbitalTools/UUID.h
)

target_compile_definitions(OrbitalTools PRIVATE OTOOLS_LIBRARY)

target_include_directories(OrbitalTools
	PUBLIC
		include
	PRIVATE
		src
)
