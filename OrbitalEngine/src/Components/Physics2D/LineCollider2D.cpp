#include "OrbitalEngine/Components/Physics2D/LineCollider2D.h"
#include "OrbitalEngine/Physics/PhysicsCalculations.h"

namespace Orbital
{
	LineCollider2D::LineCollider2D(const TransformHandle& transform, const RigidBody2DHandle& rb)
		: Collider2DComponent(transform, rb)
	{
	}

	Collision2DPoints LineCollider2D::getCollisionPoints(const Collider2DComponent& other) const
	{
		return other.getCollisionPoints(*this);
	}

	Collision2DPoints LineCollider2D::getCollisionPoints(const LineCollider2D& other) const
	{
		return Physics2D::GetLineLineCollisionPoints(*this, other);
	}

	Collision2DPoints LineCollider2D::getCollisionPoints(const CircleCollider2D& other) const
	{
		return Physics2D::GetCircleLineCollisionPoints(other, *this);
	}

	Collision2DPoints LineCollider2D::getCollisionPoints(const QuadCollider2D& other) const
	{
		return Physics2D::GetLineQuadCollisionPoints(*this, other);
	}

	Collision2DPoints LineCollider2D::getCollisionPoints(const PolygonCollider2D& other) const
	{
		return Physics2D::GetLinePolygonCollisionPoints(*this, other);
	}
} // namespace Orbital
