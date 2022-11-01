#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/Physics2D/RigidBody2D.h"

namespace Orbital
{
	class OENGINE_API LineCollider2D : public Collider2DComponent
	{
	public:
		LineCollider2D(const TransformHandle& transform, const RigidBody2DHandle& rb);

		virtual Collision2DPoints getCollisionPoints(const Collider2DComponent& other) const override;
		virtual Collision2DPoints getCollisionPoints(const LineCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const CircleCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const QuadCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const PolygonCollider2D& other) const override;

		inline const Maths::Vec2& getNormal() const
		{
			return mNormal;
		}
		inline void setNormal(const Maths::Vec2& vec)
		{
			mNormal = vec;
		}

	private:
		Maths::Vec2 mNormal = { 1.0f, 0.0f };
	};
} // namespace Orbital
