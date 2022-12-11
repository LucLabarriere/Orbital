cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<0:>${CMAKE_SOURCE_DIR}/bin")

project(Orbital VERSION 0.1.0)
#set(MEMORY_DEBUGGING="-fsanitize=address -fno-omit-frame-pointer -O1")
#add_compile_options(${MEMORY_DEBUGGING})
#add_link_options(${MEMORY_DEBUGGING})

# GTEST
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(
    GTest::GTest
    INTERFACE
    IMPORTED
)
target_link_libraries(
    GTest::GTest
    INTERFACE gtest_main
)

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
# enable_testing()

add_subdirectory(OrbitalTools)
add_subdirectory(OrbitalECS)
add_subdirectory(OrbitalRenderer)
add_subdirectory(OrbitalPhysics)
add_subdirectory(OrbitalInputs)
add_subdirectory(OrbitalEngine)
add_subdirectory(OrbitalScripts)
add_subdirectory(OrbitalEditor)
#add_subdirectory(TestProject)

