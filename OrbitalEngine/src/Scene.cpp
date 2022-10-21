#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
    Scene::Scene()
        : mRegistry()
    {

    }

    void Scene::terminate()
    {
        mRegistry.cleanUp();
    }

    void Scene::reset()
    {
        mRegistry.reset();
    }

    void Scene::onLoad()
    {
        for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
        {
            manager.onLoad();
        }
    }
        
    void Scene::onStart()
    {
        for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
        {
            manager.onStart();
        }
    }

    void Scene::onUpdate(const Time& dt)
    {
        if (Services::ScriptEngine::LastCompilationSucceeded())
        {
            for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
            {
                manager.onUpdate(dt);
            }
        }

        for (auto& [ uuid, mc ] : mRegistry.components<MeshComponent>())
        {
            Services::Renderer::Draw(mc);
        }
    }

    void Scene::onCleanUp()
    {
        for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
        {
            manager.onCleanUp();
        }

        mRegistry.reset();
    }
}

