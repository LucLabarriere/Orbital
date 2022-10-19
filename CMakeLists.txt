cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
project(Orbital VERSION 0.1.0)

# GLAD
add_subdirectory(vendor/glad)
 
# # GLM
add_subdirectory(vendor/glm)
 
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(vendor/glfw)
set(BUILD_SHARED_LIBS OFF)

# # Imgui
# add_subdirectory(vendor/imgui)

enable_testing()

add_subdirectory(OrbitalTools)
add_subdirectory(OrbitalECS)
add_subdirectory(OrbitalLogger)
add_subdirectory(OrbitalRenderer)
add_subdirectory(OrbitalInputs)
add_subdirectory(OrbitalEngine)
add_subdirectory(OrbitalScripts)
add_subdirectory(OrbitalEditor)
