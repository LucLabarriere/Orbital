#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/Components.h"

namespace Orbital
{
    Scene::Scene(SceneServiceManager services)
        : mRegistry(new Registry), mServices(services)
    {

    }

    void Scene::terminate()
    {
        mRegistry->cleanUp();
    }

    void Scene::reset()
    {
        mRegistry->reset();
    }

    Entity Scene::createEntity()
    {
        Entity e = mRegistry->createEntity();
        e.push<NativeScriptManager>(ServiceManager<ScriptEngineService>::Create(mServices.ScriptEngine));
        return e;
    }

    void Scene::onLoad()
    {
        for (auto& [ uuid, manager ] : mRegistry->components<NativeScriptManager>())
        {
            manager.onLoad();
        }
    }
        
    void Scene::onStart()
    {
        for (auto& [ uuid, manager ] : mRegistry->components<NativeScriptManager>())
        {
            manager.onStart();
        }
    }

    void Scene::onUpdate(const Time& dt)
    {
        if (mServices.ScriptEngine.LastCompilationSucceeded())
        {
            for (auto& [ uuid, manager ] : mRegistry->components<NativeScriptManager>())
            {
                manager.onUpdate(dt);
            }
        }

        for (auto& [ uuid, mc ] : mRegistry->components<MeshComponent>())
        {
            mServices.Renderer.Draw(mc);
        }
    }

    void Scene::onCleanUp()
    {
        for (auto& [ uuid, manager ] : mRegistry->components<NativeScriptManager>())
        {
            manager.onCleanUp();
        }

        mRegistry->reset();
    }
}

