#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Physics/Collider.h"

namespace Orbital
{
	class PlaneCollider : public Collider
	{
	public:
		PlaneCollider(const TransformHandle& transform);
		PlaneCollider(const TransformHandle& transform, const DynamicsHandle& dynamics);

		virtual CollisionPoints getCollisionPoints(const Collider& other) const override;
		virtual CollisionPoints getCollisionPoints(const PlaneCollider& other) const override;
		virtual CollisionPoints getCollisionPoints(const SphereCollider& other) const override;

		inline const Maths::Vec3& getNormal() const
		{
			return mNormal;
		}
		inline void setNormal(const Maths::Vec3& vec)
		{
			mNormal = vec;
		}

	private:
		Maths::Vec3 mNormal = { 1.0f, 0.0f, 0.0f };
	};
} // namespace Orbital
