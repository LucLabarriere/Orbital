#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    class ScriptsLibraryLoader;

    class OENGINE_API NativeScriptManager
    {
    public:
        NativeScriptManager(ScriptsLibraryLoader* loader);
        ~NativeScriptManager();

        void clear();
        void clearPointers();
        void clearContainer();
        void onLoad();
        void onUpdate(Time dt);
        void push(const std::string& name, const Entity& e);
        std::vector<std::string> getScriptNames() const;

    private:
        std::unordered_map<std::string, NativeScript*> mScripts;
        ScriptsLibraryLoader* mLoader;
    };
}
