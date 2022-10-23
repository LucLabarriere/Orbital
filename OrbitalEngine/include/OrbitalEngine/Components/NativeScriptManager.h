#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Services/ScriptEngineService.h"

namespace Orbital
{
    class OENGINE_API NativeScriptManager
    {
    public:
        NativeScriptManager(ServiceManager<ScriptEngineService> services);
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
        ServiceManager<ScriptEngineService> mServices;
    };
}
