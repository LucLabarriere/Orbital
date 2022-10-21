#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
    class ScriptsLibraryLoader;

    class OENGINE_API NativeScriptManager : private Services::ScriptEngine
    {
    public:
        NativeScriptManager();
        ~NativeScriptManager();

        void clear();

        void onLoad();
        void onStart();
        void onUpdate(const Time& dt);
        void onCleanUp();

        void push(const std::string& name, const Entity& e);
        std::vector<std::string> getScriptNames() const;

    private:
        std::unordered_map<std::string, NativeScript*> mScripts;
    };
}
