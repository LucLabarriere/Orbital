cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(DemoExecutable
  VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(DemoExecutable
  ${SOURCES})

target_link_libraries(DemoExecutable PRIVATE
  OrbitalEngine
  DemoLibrary)

target_include_directories(DemoExecutable PRIVATE src include ${CMAKE_CURRENT_SOURCE_DIR}/../DemoLibrary/include ${CMAKE_CURRENT_SOURCE_DIR}/../../OrbitalEngine/include)

if (WIN32)
  add_custom_command(TARGET DemoExecutable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:DemoExecutable> $<TARGET_FILE_DIR:DemoExecutable>
    COMMAND_EXPAND_LISTS)
else()
  add_custom_command(TARGET DemoExecutable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:DemoScripts> $<TARGET_FILE_DIR:DemoExecutable>
    COMMAND_EXPAND_LISTS)
endif()

add_dependencies(DemoExecutable DemoScripts)
