#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/Physics3D/RigidBody3D.h"

namespace Orbital
{
	class OENGINE_API SphereCollider3D : public Collider3DComponent
	{
	public:
		SphereCollider3D(const TransformHandle& transform, const RigidBody3DHandle& rb);

		virtual Collision3DPoints getCollisionPoints(const Collider3DComponent& other) const override;
		virtual Collision3DPoints getCollisionPoints(const PlaneCollider3D& other) const override;
		virtual Collision3DPoints getCollisionPoints(const SphereCollider3D& other) const override;
		virtual Collision3DPoints getCollisionPoints(const BoxCollider3D& other) const override;

		inline float getRadius() const
		{
			return mRadius;
		}
		inline void setRadius(float value)
		{
			mRadius = value;
		}

	private:
		float mRadius = 1.0f;
	};
} // namespace Orbital
