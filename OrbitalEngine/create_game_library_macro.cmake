macro(OrbitalEngineGameLibrary)

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
	
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME}-Library SHARED ${SOURCES})
add_library(${PROJECT_NAME}::Library ALIAS ${PROJECT_NAME}-Library)

target_precompile_headers(${PROJECT_NAME}-Library
  PRIVATE
  include/${PROJECT_NAME}Library/Context.h)

target_compile_definitions(${PROJECT_NAME}-Library
  PUBLIC
  $<$<CONFIG:Debug>:ODEBUG=1>

  PRIVATE
  ${UPPER_PROJECT_NAME}LIB_EXPORT)

target_link_libraries(
  ${PROJECT_NAME}-Library
  PUBLIC OrbitalEngine)

if(NOT WIN32)
  target_link_libraries(
    ${PROJECT_NAME}-Library
    PUBLIC dl)
endif()

target_include_directories(${PROJECT_NAME}-Library PUBLIC
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}Scripts/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../OrbitalScripts/include

  PRIVATE src)

# Asset symlink
file(
  GLOB_RECURSE
  ASSET_FILES
  assets/*.*)

add_custom_target(${PROJECT_NAME}-Library-ExportAssets ALL DEPENDS ${ASSET_FILES})

add_custom_command(
  TARGET ${PROJECT_NAME}-Library-ExportAssets
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/${PROJECT_NAME}/
  COMMAND_EXPAND_LISTS)

add_dependencies(${PROJECT_NAME}-Library-ExportAssets OrbitalEngineCreateAssetDirectory)

endmacro()
