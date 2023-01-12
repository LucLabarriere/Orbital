#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalEngine/Library.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	using ScriptsLibraryLoaderServices = Services<>;

	class OENGINE_API ScriptsLibraryLoader : public ScriptsLibraryLoaderServices
	{
	public:
		ScriptsLibraryLoader(const SharedApplication& app);
		virtual ~ScriptsLibraryLoader(){};

		void terminate();
		void registerLibrary(std::string_view libraryName);
		void registerScript(const std::string& libraryName, const std::string& scriptName);
		void loadLibraries();
		bool recompile();
		bool lastCompilationSucceeded() const
		{
			return mCompilationSucceeded;
		}
		NativeScript* createScript(const std::string& scriptName, const Entity& e);

	private:
		std::vector<Library> mLibraries;
		std::unordered_map<std::string, CreateNativeScript_t*> mCreators;

		bool mCompilationSucceeded = true;
	};
} // namespace Orbital
