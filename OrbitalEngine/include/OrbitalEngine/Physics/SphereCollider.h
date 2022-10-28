#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Physics/Collider.h"

namespace Orbital
{
	class OENGINE_API SphereCollider : public Collider
	{
	public:
		SphereCollider(const TransformHandle& transform);
		SphereCollider(const TransformHandle& transform, const DynamicsHandle& dynamics);

		virtual CollisionPoints getCollisionPoints(const Collider& other) const override;
		virtual CollisionPoints getCollisionPoints(const PlaneCollider& other) const override;
		virtual CollisionPoints getCollisionPoints(const SphereCollider& other) const override;

		inline float getRadius() const { return mRadius; }
		inline void setRadius(float value) { mRadius = value; }

	private:
		float mRadius = 1.0f;
	};
}
