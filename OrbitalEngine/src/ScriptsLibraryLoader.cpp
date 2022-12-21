#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Files.h"


namespace Orbital
{
	ScriptsLibraryLoader::ScriptsLibraryLoader(const SharedApplication& app) : ScriptsLibraryLoaderServices(app)
	{
	}

	void ScriptsLibraryLoader::initialize()
	{
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

		mLibrary = LibraryLoader::OpenLibrary((Files::GetAbsolutePath(mLibraryFileName)).c_str());

		if (!mLibrary)
		{
			LibraryLoader::LogError();
		}
		else
		{
			Logger::Debug("Library \"" + mLibraryName +  "\" loaded.");
		}
	}

	void ScriptsLibraryLoader::registerScript(const std::string& scriptName)
	{
		auto createFunction =
			(CreateNativeScript_t*)LibraryLoader::GetFunction(mLibrary, ("Create" + scriptName).c_str());

		if (!createFunction)
		{
			LibraryLoader::LogError();
			Orbital::Assert(
				createFunction, "Error while loading \"Create" + scriptName  + "\" from \"" + mLibraryName + "\" dll"
			);
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
		Orbital::Assert(
			mCreators.find(scriptName) != mCreators.end(), "The script \"" + scriptName + "\" was not registered"
		);
		return mCreators.at(scriptName)(e, mApp);
	}

	bool ScriptsLibraryLoader::recompileLibrary()
	{
#ifdef OENGINE_COMPILE_SCRIPTS
#ifdef OENGINE_DEBUG
		std::string cmd = "cmake --build " + Files::GetAbsolutePath("../build") + " --target=" + mLibraryName;
#else
		std::string cmd =
			"cmake --build " + Files::GetAbsolutePath("../build") + " --config=Release --target=" + mLibraryName;
#endif
		bool result = !(bool)std::system(cmd.c_str());
#else
		bool result = true;
#endif

		if (result)
			Logger::Debug("Recompilation of scripts was successful");

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
