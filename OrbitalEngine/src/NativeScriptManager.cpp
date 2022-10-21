#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    NativeScriptManager::NativeScriptManager()
    {

    }
    
    NativeScriptManager::~NativeScriptManager()
    {
        clear();
    }

    void NativeScriptManager::clear()
    {
        for (auto& [ name, script ] : mScripts)
        {
            // If nullptr, the clearing was already done
            if (script == nullptr)
                break;

            delete script;
            script = nullptr;
        }

        mScripts.clear();
    }

    void NativeScriptManager::onLoad()
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onLoad();
        }
    }

    void NativeScriptManager::onStart()
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onStart();
        }
    }

    void NativeScriptManager::onUpdate(const Time& dt)
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onUpdate(dt);
        }
    }

    void NativeScriptManager::onCleanUp()
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onCleanUp();
        }
    }

    void NativeScriptManager::push(const std::string& name, const Entity& e)
    {
        mScripts.emplace(name, Services::ScriptEngine::CreateScript(name, e));
    }

    std::vector<std::string> NativeScriptManager::getScriptNames() const
    {
        std::vector<std::string> names(mScripts.size());

        size_t i = 0;

        for (auto& [ name, script ] : mScripts)
        {
            names[i] = name;
            i++;
        }

        return names;
    }
}
