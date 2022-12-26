cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<0:>${CMAKE_SOURCE_DIR}/bin")
set(OE_BUILD_DOC OFF)
set(OE_COMPILE_SCRIPTS ON)

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
add_subdirectory(OrbitalDemo)
#add_subdirectory(TestProject)


if (OE_BUILD_DOC)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doxygen_Orbital ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Orbital documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endif(OE_BUILD_DOC)
