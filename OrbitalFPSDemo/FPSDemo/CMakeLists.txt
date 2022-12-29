file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE OrbitalEngine ${PROJECT_NAME}Library)

target_include_directories(${PROJECT_NAME} PRIVATE
  src include ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}Library/include ${CMAKE_CURRENT_SOURCE_DIR}/../../OrbitalEngine/include)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}Scripts)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}LibraryExportAssets)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD COMMAND
  ${CMAKE_COMMAND} -E copy $<TARGET_FILE:OrbitalScripts> $<TARGET_FILE_DIR:${PROJECT_NAME}>/)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD COMMAND
  ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}Scripts> $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
