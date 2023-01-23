#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Handle.h"

namespace Orbital
{
	// SafeHandle IMPLEMENTATIONS
	template <>
	auto SafeHandle<TransformComponent>::operator*() const -> const TransformComponent&
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<PhysicsComponent> physics =
			registry->get<PhysicsComponent>(mEntityID);

		if (physics.isValid()) { return physics->getTransform(); }

		ECS::Handle<TransformComponent> transform =
			registry->get<TransformComponent>(mEntityID);

		Orbital::Assert(
			transform.isValid(),
			"The object has no TransformComponent nor PhysicsComponent"
		);
		return *transform;
	}

	template <>
	auto SafeHandle<TransformComponent>::operator*() -> TransformComponent&
	{
		return OE_UNCONST(TransformComponent&, SafeHandle<TransformComponent>, operator*);
	}

	template <>
	auto SafeHandle<TransformComponent>::isValid() const -> bool
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();

		ECS::Handle<PhysicsComponent> physics =
			registry->get<PhysicsComponent>(mEntityID);

		if (physics.isValid()) { return true; }

		ECS::Handle<TransformComponent> transform =
			registry->get<TransformComponent>(mEntityID);

		return transform.isValid();
	}
} // namespace Orbital
