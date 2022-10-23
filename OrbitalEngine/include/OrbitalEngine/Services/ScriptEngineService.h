#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
    class OrbitalApplication;
    class ScriptsLibraryLoader;
    class NativeScript;

    struct ScriptEngineService
    {
    public:
        class ScriptEngineInterface : public ServiceInterface<ScriptsLibraryLoader>
        {
        public:
            ScriptEngineInterface(std::shared_ptr<ScriptsLibraryLoader> instance);
            
            bool LastCompilationSucceeded();
            void RegisterScript(const std::string& scriptName);
            NativeScript* CreateScript(const std::string& scriptName, const Entity& e);
            bool Reload();

        protected:
            friend Orbital::OrbitalApplication;
            void Terminate();

        } ScriptEngine = ScriptEngineInterface(nullptr);
    };
}
