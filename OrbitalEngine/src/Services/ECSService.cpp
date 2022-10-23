#include "OrbitalEngine/Services/ECSService.h"
#include "OrbitalEngine/Scene.h"

namespace Orbital
{
    ECSService::ECSInterface::ECSInterface()
        : ServiceInterface<Scene>()
        , mRegistry(nullptr)
    {

    }

    ECSService::ECSInterface::ECSInterface(std::shared_ptr<Scene> instance)
        : ServiceInterface<Scene>({ instance })
        , mRegistry(instance->mRegistry)
    {

    }

    void ECSService::ECSInterface::Reset() 
    {
        mInstance->mRegistry->reset(); 
    }

    Entity ECSService::ECSInterface::CreateEntity()
    {
        return mInstance->createEntity(); 
    }

    Entity ECSService::ECSInterface::GetEntity(const EntityID& entityID)
    {
        return mInstance->mRegistry->getEntity(entityID); 
    }
}
