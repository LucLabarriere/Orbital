macro(OrbitalEngineGameScripts)

  string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
  file(GLOB_RECURSE SOURCES src/*.cpp)

  add_library(${PROJECT_NAME}-Scripts SHARED ${SOURCES})
  add_library(${PROJECT_NAME}::Scripts ALIAS ${PROJECT_NAME}-Scripts)

  target_compile_definitions(${PROJECT_NAME}-Scripts
    PRIVATE ${UPPER_PROJECT_NAME}_SCRIPTS_EXPORT)

  target_link_libraries(${PROJECT_NAME}-Scripts PUBLIC ${PROJECT_NAME}::Library Orbital::Engine)

  target_include_directories(${PROJECT_NAME}-Scripts PUBLIC include PRIVATE src)

endmacro()
