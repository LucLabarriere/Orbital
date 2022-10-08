#include "OrbitalECS/ECS.h"

namespace Orbital
{
    Entity Registry::createEntity()
    {
        return Entity(
            this,
            *mEntities.emplace().first
        );
    }
}
