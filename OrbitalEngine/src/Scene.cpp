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
        for (auto& [ uuid, manager ] : Services::Scene::Components<NativeScriptManager>())
        {
            manager.onLoad();
        }
    }
        
    void Scene::onStart()
    {
        for (auto& [ uuid, manager ] : Services::Scene::Components<NativeScriptManager>())
        {
            manager.onStart();
        }
    }

    void Scene::onUpdate(const Time& dt)
    {
        if (Services::ScriptEngine::LastCompilationSucceeded())
        {
            for (auto& [ uuid, manager ] : Services::Scene::Components<NativeScriptManager>())
            {
                manager.onUpdate(dt);
            }
        }

        for (auto& [ uuid, mc ] : Services::Scene::Components<MeshComponent>())
        {
            Services::Renderer::Draw(mc);
        }
    }

    void Scene::onCleanUp()
    {
        for (auto& [ uuid, manager ] : Services::Scene::Components<NativeScriptManager>())
        {
            manager.onCleanUp();
        }

        mRegistry.reset();
    }
}

