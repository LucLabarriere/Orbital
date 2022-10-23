#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
    SceneManager::SceneManager(SceneServiceManager services)
        : mServices(services), mScene(new Scene(services))
    {
        
    }

    void SceneManager::terminate()
    {
        mScene->terminate();
    }

    void SceneManager::onLoad()
    {
        mScene->onLoad();
    }

    void SceneManager::onCleanUp()
    {
        mScene->onCleanUp();
    }

    void SceneManager::onStart()
    {
        mScene->onStart();
    }

    void SceneManager::onUpdate(const Time& dt)
    {
        mScene->onUpdate(dt);
    }
}
