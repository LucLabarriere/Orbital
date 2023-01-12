macro(OrbitalEngineGameExecutable)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}::Library)
target_include_directories(${PROJECT_NAME} PRIVATE src include)

add_custom_target(${PROJECT_NAME}-CopyLibraryFiles ALL)
add_dependencies(${PROJECT_NAME}
	Orbital-ExportAssets
	${PROJECT_NAME}::Scripts)

add_custom_command(TARGET ${PROJECT_NAME}-CopyLibraryFiles
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Orbital::Scripts> $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
add_custom_command(TARGET ${PROJECT_NAME}-CopyLibraryFiles
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}::Scripts> $<TARGET_FILE_DIR:${PROJECT_NAME}>/)

add_dependencies(${PROJECT_NAME}
	${PROJECT_NAME}-CopyLibraryFiles)

endmacro()
