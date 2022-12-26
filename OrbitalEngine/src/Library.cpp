#include "OrbitalEngine/Library.h"
#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	Library::Library(const std::string& libraryName) : mLibraryName(libraryName)
	{
#ifdef _WIN32
		std::string mLibraryFileName = libraryName + ".dll";
#else // Linux
		std::string mLibraryFileName = "lib" + libraryName + ".so";
#endif

		mLibraryPath = Files::GetAbsolutePath(mLibraryFileName);
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

	void Library::close()
	{
		LibraryLoader::CloseLibrary(mHandle);
	}

	void Library::registerScript(const std::string& scriptName)
	{
		mScripts.emplace_back(scriptName);
	}
} // namespace Orbital
