add_library(OrbitalECS SHARED
src/Handle.cpp
src/Registry.cpp
include/OrbitalECS/Context.h
include/OrbitalECS/EntityHandle.h
include/OrbitalECS/Handle.h
include/OrbitalECS/Pool.h
include/OrbitalECS/Registry.h
)

target_compile_definitions(OrbitalECS PUBLIC OECS_LIBRARY)

target_include_directories(OrbitalECS
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/OrbitalTools/include
	PRIVATE
		src
)