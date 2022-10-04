add_library(OrbitalScripts SHARED ${SOURCES})

target_compile_definitions(OrbitalScripts PUBLIC OESCRIPTS_LIBRARY)

target_include_directories(OrbitalScripts
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
		include
	PRIVATE
		src
)

target_link_libraries(OrbitalScripts PRIVATE OrbitalEngine)