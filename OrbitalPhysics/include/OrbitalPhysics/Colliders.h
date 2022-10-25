#pragma once

#include "OrbitalPhysics/Tools.h"

namespace Orbital
{
	class PlaneCollider;

	class Collider

	{
	public:
		virtual Physics::CollisionPoints GetCollisionPoints(
			const Physics::Transform* transform, const Collider* collider, const Physics::Transform* otherTransform
		) const = 0;

		virtual Physics::CollisionPoints GetCollisionPoints(
			const Physics::Transform* transform, const PlaneCollider* collider, const Physics::Transform* otherTransform
		) const = 0;
	};

	class PlaneCollider : public Collider
	{
	public:
		virtual Physics::CollisionPoints GetCollisionPoints(
			const Physics::Transform* transform, const Collider* collider, const Physics::Transform* otherTransform
		) const override
		{
			return collider->GetCollisionPoints(otherTransform, this, transform);
		}

		virtual Physics::CollisionPoints GetCollisionPoints(
			const Physics::Transform* transform, const PlaneCollider* collider, const Physics::Transform* otherTransform
		) const override;
	};
} // namespace Orbital
