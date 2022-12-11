#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"

#include "OrbitalPhysics/Engine.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	Entity ECSManager::createEntity()
	{
		return Entity(mRegistry.createEntity().getID(), shared_from_this());
	}

	Entity ECSManager::getEntity(const EntityID& id)
	{
		return Entity(id, shared_from_this());
	}

	void ECSManager::deleteEntity(const EntityID& id)
	{
		mRegistry.deleteEntity(id);
	}

	PhysicsHandle ECSManager::addPhysicsComponent(const EntityID& id, ColliderType colliderType)
	{
		switch (colliderType)
		{
		case ColliderType::POINT_COLLIDER:
		{
			std::shared_ptr<Physics::Collider> collider = nullptr;
			mRegistry.push<PhysicsComponent>(id, collider);
			break;
		}
		case ColliderType::SPHERE_COLLIDER:
		{
			auto collider = std::make_shared<Physics::SphereCollider>();
			mRegistry.push<PhysicsComponent>(id, static_pointer_cast<Physics::Collider>(collider));
			break;
		}
		}
		return SafeHandle<PhysicsComponent>(id, shared_from_this());
	}
}
