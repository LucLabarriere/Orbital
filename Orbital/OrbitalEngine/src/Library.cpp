#include "OrbitalEngine/Library.h"
#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Files.h"

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

	auto Library::open() -> bool
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
			auto creator = (CreateNativeScript_t*)LibraryLoader::GetFunction(
				mHandle, ("Create" + script.getName()).c_str()
			);

			if (!creator)
			{
				LibraryLoader::LogError();
				Orbital::Assert(
					creator, "Error while loading \"Create" + script.getName() +
								 "\" from \"" + mLibraryPath
				);
			}

			script.setCreator(creator);
		}
	}

	auto Library::compile() -> bool
	{
		bool result = false;

#ifdef OENGINE_DEBUG
		std::string cmd = "cmake --build " + Files::AbsolutePath("../build") +
						  " --target=" + mLibraryName;
#else
		std::string cmd = "cmake --build " + Files::AbsolutePath("../build") +
						  " --config=Release --target=" + mLibraryName;
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

	void Library::registerScript(std::string_view scriptName)
	{
		mScripts.emplace_back(std::string(scriptName));
	}
} // namespace Orbital
