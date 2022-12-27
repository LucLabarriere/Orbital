cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 23)
project(FPSDemoExecutable
  VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(FPSDemoExecutable
  ${SOURCES})

target_link_libraries(FPSDemoExecutable PRIVATE
  OrbitalEngine
  FPSDemoLibrary)

target_include_directories(FPSDemoExecutable PRIVATE src include ${CMAKE_CURRENT_SOURCE_DIR}/../FPSDemoLibrary/include ${CMAKE_CURRENT_SOURCE_DIR}/../../OrbitalEngine/include)

if (WIN32)
  add_custom_command(TARGET FPSDemoExecutable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:FPSDemoExecutable> $<TARGET_FILE_DIR:FPSDemoExecutable>
    COMMAND_EXPAND_LISTS)
else()
  add_custom_command(TARGET FPSDemoExecutable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:FPSDemoScripts> $<TARGET_FILE_DIR:FPSDemoExecutable>
    COMMAND_EXPAND_LISTS)
endif()

add_dependencies(FPSDemoExecutable FPSDemoScripts)
