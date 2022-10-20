#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    class ScriptsLibraryLoader;

    class OENGINE_API NativeScriptManager
    {
    public:
        NativeScriptManager();
        ~NativeScriptManager();

        void clear();
        void clearPointers();
        void clearContainer();
        void onLoad();
        void onUpdate(Time& dt);
        void push(const std::string& name, const Entity& e);
        std::vector<std::string> getScriptNames() const;
        
        static void SetLibraryLoader(ScriptsLibraryLoader* loader) { sLoader = loader; } // TODO, make it a service

    private:
        std::unordered_map<std::string, NativeScript*> mScripts;
        static inline ScriptsLibraryLoader* sLoader = nullptr;
    };
}
