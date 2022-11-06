#include "OrbitalEngine/Components/Physics2D/CircleCollider2D.h"
#include "OrbitalEngine/Physics/PhysicsCalculations.h"

namespace Orbital
{
	CircleCollider2D::CircleCollider2D(const TransformHandle& transform, const RigidBody2DHandle& body)
		: Collider2DComponent(transform, body)
	{
	}

	Collision2DPoints CircleCollider2D::getCollisionPoints(const Collider2DComponent& other) const
	{
		return other.getCollisionPoints(*this);
	}

	Collision2DPoints CircleCollider2D::getCollisionPoints(const LineCollider2D& other) const
	{
		return Physics2D::GetCircleLineCollisionPoints(*this, other);
	}

	Collision2DPoints CircleCollider2D::getCollisionPoints(const CircleCollider2D& other) const
	{
		return Physics2D::GetCircleCircleCollisionPoints(*this, other);
	}

	Collision2DPoints CircleCollider2D::getCollisionPoints(const QuadCollider2D& other) const
	{
		return Physics2D::GetCircleQuadCollisionPoints(*this, other);
	}

	Collision2DPoints CircleCollider2D::getCollisionPoints(const PolygonCollider2D& other) const
	{
		return Physics2D::GetCirclePolygonCollisionPoints(*this, other);
	}
} // namespace Orbital
