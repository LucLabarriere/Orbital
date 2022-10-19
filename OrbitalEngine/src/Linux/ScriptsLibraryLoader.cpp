#ifndef _WIN32

#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalTools/Files.h"
#include <dlfcn.h>
#include <cstdlib>

namespace Orbital
{
    void ScriptsLibraryLoader::open()
    {
        mLibrary = dlopen(
            (Files::getPathToBinaryDirectory() + "/libOrbitalScripts.so").c_str(),
            RTLD_LAZY
        );

        if (!mLibrary)
        {
            Logger::Error(dlerror());
        }
    }

    void ScriptsLibraryLoader::registerScript(const std::string& scriptName)
    {
        dlerror();

        auto createFunc = (CreateNativeScript_t*)dlsym(
            mLibrary, ("Create" + scriptName).c_str()
        );
        const char* dlsym_error = dlerror();

        if (dlsym_error)
        {
            Logger::Error("Cannot load symbol ", scriptName, ": ",  dlsym_error);
            return;
        }

        mCreators.emplace(scriptName, createFunc);
    }

    void ScriptsLibraryLoader::close()
    {
        dlclose(mLibrary);
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
