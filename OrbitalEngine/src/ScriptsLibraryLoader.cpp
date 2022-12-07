#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Files.h"

#ifdef _WIN32
#define SCRIPTS_LIBRARY_NAME "OrbitalScripts.dll"
#else // Linux
#define SCRIPTS_LIBRARY_NAME "libOrbitalScripts.so"
#endif

namespace Orbital
{
	ScriptsLibraryLoader::ScriptsLibraryLoader(const SharedApplication& app) : ScriptsLibraryLoaderServices(app)
	{
		LOGFUNC();
	}

	void ScriptsLibraryLoader::initialize()
	{
		LOGFUNC();
		open();
	}

	void ScriptsLibraryLoader::terminate()
	{
		LOGFUNC();
		close();
	}

	void ScriptsLibraryLoader::open()
	{
		LibraryLoader::GetError(); // Clearing errors

		mLibrary = LibraryLoader::OpenLibrary((Files::GetAbsolutePath(SCRIPTS_LIBRARY_NAME)).c_str());

		if (!mLibrary)
		{
			LibraryLoader::LogError();
		}
	}

	void ScriptsLibraryLoader::registerScript(const std::string& scriptName)
	{
		auto createFunction =
			(CreateNativeScript_t*)LibraryLoader::GetFunction(mLibrary, ("Create" + scriptName).c_str());

		if (!createFunction)
		{
			LibraryLoader::LogError();
			return;
		}

		mCreators.emplace(scriptName, createFunction);
	}

	void ScriptsLibraryLoader::close()
	{
		LibraryLoader::CloseLibrary(mLibrary);
	}

	bool ScriptsLibraryLoader::reload()
	{
		// If last compilation failed
		if (!mSucceeded)
		{
			mSucceeded = recompileLibrary();

			if (mSucceeded)
			{
				open();
				// Register scripts from saved names
				for (auto& key : mScriptNames)
					registerScript(key);

				return true;
			}

			return false;
		}
		else // If last compilation succeeded
		{
			saveScriptNames();

			mCreators.clear();
			close();

			mSucceeded = recompileLibrary();

			if (mSucceeded)
			{
				open();
				for (auto& key : mScriptNames)
					registerScript(key);
				return true;
			}
			return false;
		}
	}

	NativeScript* ScriptsLibraryLoader::createScript(const std::string& scriptName, const Entity& e)
	{
		return mCreators.at(scriptName)(e, mApp);
	}

	bool ScriptsLibraryLoader::recompileLibrary()
	{
#ifdef OENGINE_DEBUG
		std::string cmd = "cmake --build " + Files::GetAbsolutePath("../build") + " --target OrbitalScripts";
#else
		std::string cmd =
			"cmake --build " + Files::GetAbsolutePath("../build") + " --target OrbitalScripts --config=Release";
#endif

		bool result = !(bool)std::system(cmd.c_str());

		if (result)
			Logger::Log("Recompilation of scripts was successful");

		else
			Logger::Error("An error occured during recompilation");

		return result;
	}

	void ScriptsLibraryLoader::saveScriptNames()
	{
		mScriptNames.clear();

		size_t i = 0;
		for (auto& [key, creators] : mCreators)
		{
			mScriptNames.emplace(key);
			i += 1;
		}
	}
} // namespace Orbital
