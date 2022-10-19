#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    class OENGINE_API ScriptsLibraryLoader
    {
    public:
        void open();
        void close();
        void reload();
        void registerScript(const std::string& scriptName);
        NativeScript* createScript(const std::string& scriptName, const Entity& e);
        void recompileLibrary();

    private:
        void* mLibrary = nullptr;
        std::unordered_map<std::string, CreateNativeScript_t*> mCreators;
    };
}
