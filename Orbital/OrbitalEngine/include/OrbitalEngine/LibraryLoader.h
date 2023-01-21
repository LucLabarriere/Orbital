#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API LibraryLoader
	{
	public:
		static void* OpenLibrary(const char* path);
		static void CloseLibrary(void* libraryHandle);
		static void* GetFunction(void* libraryHandle, const char* functionName);
		static const char* GetError();
		static void LogError();
	};
} // namespace Orbital
