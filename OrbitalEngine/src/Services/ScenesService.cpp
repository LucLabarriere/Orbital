#include "OrbitalEngine/Services/ScenesService.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
    ScenesService::ScenesInterface::ScenesInterface(std::shared_ptr<SceneManager> instance)
        : ServiceInterface<SceneManager>(instance) 
    { 

    }

    void ScenesService::ScenesInterface::OnLoad() 
    {
        mInstance->onLoad(); 
    }

    void ScenesService::ScenesInterface::OnCleanUp() 
    {
        mInstance->onCleanUp(); 
    }

    void ScenesService::ScenesInterface::OnStart()
    {
        mInstance->onStart();
    }

    void ScenesService::ScenesInterface::OnUpdate(const Time& dt)
    {
        mInstance->onUpdate(dt);
    }

    void ScenesService::ScenesInterface::Terminate()
    {
        mInstance->terminate();
    }
}
