#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API LibraryLoader
	{
	public:
		static auto OpenLibrary(const char* path) -> void*;
		static void CloseLibrary(void* libraryHandle);
		static auto GetFunction(void* libraryHandle, const char* functionName) -> void*;
		static auto GetError() -> const char*;
		static void LogError();
	};
} // namespace Orbital
