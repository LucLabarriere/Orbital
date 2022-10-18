#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
    NativeScriptManager::NativeScriptManager(ScriptsLibraryLoader* loader)
        : mLoader(loader)
    {

    }
    
    NativeScriptManager::~NativeScriptManager()
    {
        clear();
    }

    void NativeScriptManager::clear()
    {
        clearPointers();
        clearContainer();
    }

    void NativeScriptManager::clearContainer()
    {
        mScripts.clear();
    }

    void NativeScriptManager::clearPointers()
    {
        for (auto& [ name, script ] : mScripts)
        {
            delete script;
        }
    }

    void NativeScriptManager::onLoad()
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onLoad();
        }
    }

    void NativeScriptManager::onUpdate(Time dt)
    {
        for (auto& [ name, script ] : mScripts)
        {
            script->onUpdate(dt);
        }
    }

    void NativeScriptManager::push(const std::string& name, const Entity& e)
    {
        mScripts.emplace(name, mLoader->createScript(name, e));
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
