#include "OrbitalEngine/Library.h"
#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Files.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	Library::Library(std::string_view libraryName) : mLibraryName(libraryName)
	{
#ifdef _WIN32
		std::string mLibraryFileName = libraryName + ".dll";
#else // Linux
		std::string mLibraryFileName = "lib" + mLibraryName + ".so";
#endif

		mLibraryPath = Files::AbsolutePath(mLibraryFileName);
	}

	bool Library::open()
	{
		LibraryLoader::GetError(); // Clearing errors
		mHandle = LibraryLoader::OpenLibrary(mLibraryPath.c_str());

		if (!mHandle)
		{
			LibraryLoader::LogError();
			return false;
		}

		Logger::Debug("Library \"" + mLibraryName + "\" loaded.");

		return true;
	}

	void Library::load()
	{
		open();

		for (auto& script : mScripts)
		{
			LibraryLoader::GetError();
			auto creator = (CreateNativeScript_t*)LibraryLoader::GetFunction(mHandle, ("Create" + script.getName()).c_str());

			if (!creator)
			{
				LibraryLoader::LogError();
				Orbital::Assert(creator, "Error while loading \"Create" + script.getName() + "\" from \"" + mLibraryPath);
			}

			script.setCreator(creator);
		}
	}

	bool Library::compile()
	{
		bool result = false;

#ifdef OENGINE_DEBUG
		std::string cmd = "cmake --build " + Files::AbsolutePath("../build") + " --target=" + mLibraryName;
#else
		std::string cmd =
			"cmake --build " + Files::AbsolutePath("../build") + " --config=Release --target=" + mLibraryName;
#endif
		result = !(bool)std::system(cmd.c_str());

		if (result)
			Logger::Debug("Recompilation of scripts was successful");

		else
			Logger::Error("An error occured during recompilation");

		return result;
	}

	void Library::close()
	{
		LibraryLoader::CloseLibrary(mHandle);
	}

	void Library::registerScript(const std::string& scriptName)
	{
		mScripts.emplace_back(scriptName);
	}
} // namespace Orbital
