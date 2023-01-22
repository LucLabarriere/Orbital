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

	auto ECSManager::createEntity() -> Entity
	{
		return Entity(mApp, mRegistry.createEntity().getID(), shared_from_this());
	}

	auto ECSManager::getEntity(const EntityID& id) -> Entity
	{
		return Entity(mApp, id, shared_from_this());
	}

	void ECSManager::deleteRequested()
	{
		for (auto& id : mRequestedDeletes)
		{
			if (isEntityValid(id)) deleteEntity(id);
		}

		mRequestedDeletes.clear();
	}

	void ECSManager::deleteEntity(const EntityID& id)
	{
		Renderer.UnregisterMeshComponent(id);
		PhysicsEngine.ClearComponents(id);
		mRegistry.deleteEntity(id);
	}

	void ECSManager::requestDeleteEntity(const EntityID& id)
	{
		mRequestedDeletes.push_back(id);
	}

	auto ECSManager::entityExists(const EntityID& id) -> bool
	{
		return mRegistry.isEntityValid(id);
	}
} // namespace Orbital
