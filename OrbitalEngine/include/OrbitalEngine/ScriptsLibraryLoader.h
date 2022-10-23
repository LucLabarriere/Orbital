#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Services/ServiceManager.h"

namespace Orbital
{
    class ScriptEngineInterface;

    class OENGINE_API ScriptsLibraryLoader
    {
    public:
        ScriptsLibraryLoader();

        void setServices(ScriptServiceManager services);
        void open();
        void close();
        bool reload();
        void registerScript(const std::string& scriptName);
        NativeScript* createScript(const std::string& scriptName, const Entity& e);
        bool recompileLibrary();
        bool lastCompilationSucceeded() const { return mSucceeded; }

    private:
        void saveScriptNames();

    private:
        friend ScriptEngineInterface;

        void* mLibrary = nullptr;
        std::unordered_map<std::string, CreateNativeScript_t*> mCreators;
        std::unordered_set<std::string> mScriptNames;
        bool mSucceeded = true;
        ScriptServiceManager mServices;
    };
}
