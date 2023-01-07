cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(Orbital VERSION 0.3.0)

add_compile_definitions("_CRT_SECURE_NO_WARNINGS")

add_subdirectory(OrbitalTools)
add_subdirectory(OrbitalECS)
add_subdirectory(OrbitalRenderer)
add_subdirectory(OrbitalPhysics)
add_subdirectory(OrbitalInputs)
add_subdirectory(OrbitalEngine)
add_subdirectory(OrbitalScripts)
add_subdirectory(OrbitalImGui)
