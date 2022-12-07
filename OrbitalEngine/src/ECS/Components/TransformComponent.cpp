#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"

namespace Orbital
{
	// SafeHandle IMPLEMENTATIONS
	template <>
	const TransformComponent& SafeHandle<TransformComponent>::operator*() const
	{
		const ECS::Registry* registry = mManager->getRegistry();
			ECS::Handle<PhysicsComponent> physics = registry->get<PhysicsComponent>(mEntityID);

			if (physics.isValid())
			{
				return physics->getTransform();
			}

			ECS::Handle<TransformComponent> transform = registry->get<TransformComponent>(mEntityID);

			assert(transform.isValid() && "The object has no TransformComponent nor PhysicsComponent");
			return *transform;
	}

	template <>
	TransformComponent& SafeHandle<TransformComponent>::operator*()
	{
		return OE_UNCONST(TransformComponent&, SafeHandle<TransformComponent>, operator*);
	}

	template <>
	bool SafeHandle<TransformComponent>::isValid() const
	{
		const ECS::Registry* registry = mManager->getRegistry();
		
		ECS::Handle<PhysicsComponent> physics = registry->get<PhysicsComponent>(mEntityID);

		if (physics.isValid())
		{
			return true; 
		}

		ECS::Handle<TransformComponent> transform = registry->get<TransformComponent>(mEntityID);

		return transform.isValid();
	}
}
