#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/Physics2D/RigidBody2D.h"

namespace Orbital
{
	class OENGINE_API CircleCollider2D : public Collider2DComponent
	{
	public:
		CircleCollider2D(const TransformHandle& transform, const RigidBody2DHandle& rb);

		virtual Collision2DPoints getCollisionPoints(const Collider2DComponent& other) const override;
		virtual Collision2DPoints getCollisionPoints(const LineCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const CircleCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const QuadCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const PolygonCollider2D& other) const override;

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
