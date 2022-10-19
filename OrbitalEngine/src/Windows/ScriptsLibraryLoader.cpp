#ifdef _WIN32

#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalTools/Files.h"
#include <windows.h>
#include <cstdlib>

namespace Orbital
{
    void PrintLastError() {
        DWORD errCode = GetLastError();
        char *err;
        if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           errCode,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
                           (LPTSTR) &err,
                           0,
                           NULL))
            return;

        static char buffer[MAX_PATH];
        _snprintf(buffer, sizeof(buffer), "ERROR: %s: %s\n", "Windows", err);
        Logger::Error(buffer);
        LocalFree(err);
    }

    void ScriptsLibraryLoader::open()
    {
        std::string libraryPath = Files::getPathToBinaryDirectory() + "/OrbitalScripts.dll";

        mLibrary = (void*)LoadLibrary(
           libraryPath.c_str() 
        );

        if (mLibrary == nullptr)
        {
            Logger::Error("Error, could not load ", libraryPath);
            PrintLastError();
        }
    }

    void ScriptsLibraryLoader::registerScript(const std::string& scriptName)
    {
        auto createFunc = (CreateNativeScript_t*)GetProcAddress(
            static_cast<HINSTANCE>(mLibrary), ("Create" + scriptName).c_str()
        );

        if (createFunc == nullptr)
        {
            Logger::Error("Error, could not load Create", scriptName, " function from the dll");
            PrintLastError();
        }

        mCreators.emplace(scriptName, createFunc);
    }

    void ScriptsLibraryLoader::close()
    {
        FreeLibrary(static_cast<HINSTANCE>(mLibrary));
    }

    void ScriptsLibraryLoader::reload()
    {
        std::vector<std::string> scriptNames(mCreators.size());
        size_t i = 0;
        for (auto& [ key, creators] : mCreators)
        {
            scriptNames[i] = key;
            i+= 1;
        }
        
        mCreators.clear();

        close();
        recompileLibrary();
        open();
        

        for (auto& key : scriptNames)
        {
            registerScript(key);
        }
    }

    NativeScript* ScriptsLibraryLoader::createScript(const std::string& scriptName, const Entity& e)
    {
        return mCreators.at(scriptName)(e);
    }

    void ScriptsLibraryLoader::recompileLibrary()
    {
        std::system(("cmake --build " + Files::getPathToBinaryDirectory() + "/../OrbitalScripts/ --target OrbitalScripts").c_str());
    }
}

#endif
