#include "OrbitalEngine/Services/ScriptEngineService.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
    ScriptEngineService::ScriptEngineInterface::ScriptEngineInterface(std::shared_ptr<ScriptsLibraryLoader> instance) 
        : ServiceInterface<ScriptsLibraryLoader>(instance)
    {

    }
    
    bool ScriptEngineService::ScriptEngineInterface::LastCompilationSucceeded()
    { 
        return mInstance->lastCompilationSucceeded();
    }

    void ScriptEngineService::ScriptEngineInterface::RegisterScript(const std::string& scriptName)
    {
        mInstance->registerScript(scriptName);
    }

    NativeScript* ScriptEngineService::ScriptEngineInterface::CreateScript(const std::string& scriptName, const Entity& e)
    {
        return mInstance->createScript(scriptName, e);
    }

    bool ScriptEngineService::ScriptEngineInterface::Reload()
    {
        return mInstance->reload();
    }

    void ScriptEngineService::ScriptEngineInterface::Terminate()
    {
        mInstance->close();
    }
}
