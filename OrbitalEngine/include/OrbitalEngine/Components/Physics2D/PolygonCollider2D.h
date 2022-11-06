#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/Physics2D/RigidBody2D.h"

namespace Orbital
{
	class OENGINE_API PolygonCollider2D : public Collider2DComponent
	{
	public:
		PolygonCollider2D(const TransformHandle& transform, const RigidBody2DHandle& rb);

		virtual Collision2DPoints getCollisionPoints(const Collider2DComponent& other) const override;
		virtual Collision2DPoints getCollisionPoints(const LineCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const CircleCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const QuadCollider2D& other) const override;
		virtual Collision2DPoints getCollisionPoints(const PolygonCollider2D& other) const override;
	};
} // namespace Orbital
