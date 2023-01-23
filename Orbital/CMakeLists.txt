cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

project(Orbital VERSION 0.3.0)

#add_compile_definitions("_CRT_SECURE_NO_WARNINGS")

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-function -Wno-unused-parameter -Wno-unused-private-field)
endif()

set(ORBITAL_IMGUI_GLFWEXAMPLE OFF)
set(ORBITAL_IMGUI_DEMO ON)
add_compile_definitions(ORBITAL_DEV)

add_subdirectory(OrbitalTools)
add_subdirectory(OrbitalECS)
add_subdirectory(OrbitalRenderer)
add_subdirectory(OrbitalPhysics)
add_subdirectory(OrbitalInputs)
add_subdirectory(OrbitalImGui)
add_subdirectory(OrbitalEngine)
add_subdirectory(OrbitalScripts)
