#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptHandle.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	ScriptsLibraryLoader::ScriptsLibraryLoader(const SharedApplication& app)
		: ScriptsLibraryLoaderServices(app), mLibraries()
	{
	}

	void ScriptsLibraryLoader::terminate()
	{
		if (mCompilationSucceeded)
		{
			for (auto& library : mLibraries)
				library.close();
		}
	}

	void ScriptsLibraryLoader::registerLibrary(std::string_view libraryName)
	{
		mLibraries.emplace_back(libraryName);
	}

	void ScriptsLibraryLoader::registerScript(
		std::string_view libraryName, const std::string& scriptName
	)
	{
		for (auto& library : mLibraries)
		{
			if (library.getLibraryName() == libraryName)
				library.registerScript(scriptName);
		}

		mCreators[scriptName] = nullptr;
	}

	void ScriptsLibraryLoader::loadLibraries()
	{
		for (auto& library : mLibraries)
		{
			library.load();

			for (auto& script : library)
			{
				mCreators[script.getName()] = script.getCreator();
			}
		}
	}

	auto ScriptsLibraryLoader::recompile() -> bool
	{
		for (auto& library : mLibraries)
		{
			library.close();
		}

#define OE_COMPILE_SCRIPTS
#ifdef OE_COMPILE_SCRIPTS
		for (auto& library : mLibraries)
		{
			mCompilationSucceeded = library.compile();

			if (!mCompilationSucceeded) break;
		}
#endif

		for (auto& library : mLibraries)
		{
			library.load();

			for (auto& script : library)
			{
				mCreators[script.getName()] = script.getCreator();
			}
		}

		return mCompilationSucceeded;
	}

	auto ScriptsLibraryLoader::createScript(
		const std::string& scriptName, const Entity& e
	) -> NativeScript*
	{
		Orbital::Assert(
			mCreators.find(scriptName) != mCreators.end(),
			"The script \"" + scriptName + "\" was not registered"
		);
		Orbital::Assert(
			mCreators[scriptName],
			"The script \"" + scriptName +
				"\"  was registered but not loaded from the library"
		);

		return mCreators.at(scriptName)(e, mApp);
	}
} // namespace Orbital
