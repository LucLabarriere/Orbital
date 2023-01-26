#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalEngine/Library.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	using ScriptsLibraryLoaderServices = Services<>;

	class ORBITAL_ENGINE_API ScriptsLibraryLoader : public ScriptsLibraryLoaderServices
	{
	public:
		ScriptsLibraryLoader(const SharedApplication& app);
		virtual ~ScriptsLibraryLoader() = default;

		void terminate();
		void registerLibrary(std::string_view libraryName);
		void registerScript(std::string_view libraryName, const std::string& scriptName);
		void loadLibraries();
		auto recompile() -> bool;
		auto lastCompilationSucceeded() const -> bool { return mCompilationSucceeded; }
		auto createScript(const std::string& scriptName, const Entity& e)
			-> NativeScript*;

	private:
		std::vector<Library> mLibraries;
		std::unordered_map<std::string, CreateNativeScript_t*> mCreators;

		bool mCompilationSucceeded = true;
	};
} // namespace Orbital
