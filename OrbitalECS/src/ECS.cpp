#include "OrbitalECS/ECS.h"
#include <stdexcept>

namespace Orbital
{
    Entity Registry::createEntity()
    {
        return Entity(
            this,
            *mEntities.emplace().first
        );
    }

    Entity Registry::getEntity(const EntityID& id)
    {
        auto entity = mEntities.find(id);
            
        if (entity != mEntities.end())
            return Entity(this, *entity);

        throw std::out_of_range(
            "Entity does not exist in the registry. This is a bug,"
            "it should not happend"
        );
    }
}