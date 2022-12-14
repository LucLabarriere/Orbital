#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Entity.h"

#include "OrbitalPhysics/Colliders.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	void ECSManager::cleanUp()
	{
		Renderer.ClearComponents();
		PhysicsEngine.ClearComponents();
		mRegistry.cleanUp();
	}

	void ECSManager::reset()
	{
		Renderer.ClearComponents();
		PhysicsEngine.ClearComponents();
		mRegistry.reset();
	}

	Entity ECSManager::createEntity()
	{
		return Entity(mApp, mRegistry.createEntity().getID(), shared_from_this());
	}

	Entity ECSManager::getEntity(const EntityID& id)
	{
		return Entity(mApp, id, shared_from_this());
	}

	void ECSManager::deleteEntity(const EntityID& id)
	{
		Renderer.UnregisterMeshComponent(id);
		PhysicsEngine.ClearComponents(id);
		mRegistry.deleteEntity(id);
	}
} // namespace Orbital
