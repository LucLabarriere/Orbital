#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalTools/Files.h"
#include "OrbitalEngine/LibraryLoader.h"

#ifdef _WIN32
#define SCRIPTS_LIBRARY_NAME "OrbitalScripts.dll"
#else // Linux
#define SCRIPTS_LIBRARY_NAME "libOrbitalScripts.so"
#endif

namespace Orbital
{
    ScriptsLibraryLoader::ScriptsLibraryLoader()
        : mServices()
    {
        open();
    }

    void ScriptsLibraryLoader::setServices(ScriptServiceManager services)
    {
        mServices = services;
    }

    void ScriptsLibraryLoader::open()
    {
        LibraryLoader::GetError(); // Clearing errors

        mLibrary = LibraryLoader::OpenLibrary(
            (Files::GetAbsolutePath(SCRIPTS_LIBRARY_NAME)).c_str()
        );

        if (!mLibrary)
        {
            LibraryLoader::LogError();
        }
    }

    void ScriptsLibraryLoader::registerScript(const std::string& scriptName)
    {
        auto createFunction = (CreateNativeScript_t*)LibraryLoader::GetFunction(
            mLibrary, ("Create" + scriptName).c_str()
        );

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
        return mCreators.at(scriptName)(e, mServices);
    }

    bool ScriptsLibraryLoader::recompileLibrary()
    {
        std::string cmd = "cmake --build " + Files::GetAbsolutePath("../build") + " --target OrbitalScripts";

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
        for (auto& [ key, creators] : mCreators)
        {
            mScriptNames.emplace(key);
            i+= 1;
        }
    }
}
