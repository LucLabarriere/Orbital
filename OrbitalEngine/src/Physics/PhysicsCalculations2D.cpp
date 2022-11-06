#include "OrbitalEngine/Physics/PhysicsCalculations.h"
#include "OrbitalEngine/Components/Physics2D/Colliders2D.h"
#include "OrbitalEngine/Physics/GJK.h"

namespace Orbital
{
	Collision2DPoints Physics2D::GetCircleCircleCollisionPoints(const CircleCollider2D& c1, const CircleCollider2D& c2)
	{
		Maths::Vec2 vector = c2.getTransform()->position - c1.getTransform()->position;
		float distance = Maths::Magnitude(vector);
		Maths::Vec2 normal = vector / distance;
		float penetrationDistance = c1.getRadius() + c2.getRadius() - distance;
		Maths::Vec2 penetrationVector = penetrationDistance * normal;

		return {
			.A = c1.getTransform()->position,
			.B = c2.getTransform()->position,
			.penetrationVector = penetrationVector,
			.normal = normal,
			.penetrationDistance = penetrationDistance,
			.collide = (penetrationDistance > 0.0f ? true : false),
		};
	}
	Collision2DPoints Physics2D::GetCircleLineCollisionPoints(const CircleCollider2D& c, const LineCollider2D& l)
	{
		Maths::Vec2 diffVector = c.getTransform()->position - l.getTransform()->position;
		float projection = Maths::Dot(diffVector, l.getNormal());
		float distance = Maths::Absolute(projection);
		float penetrationDistance = c.getRadius() - distance;
		bool collide = (c.getRadius() - projection > 0.0f ? true : false);

		return {
			.A = l.getTransform()->position,
			.B = c.getTransform()->position,
			.penetrationVector = l.getNormal() * penetrationDistance,
			.normal = l.getNormal(),
			.penetrationDistance = penetrationDistance,
			.collide = collide,
		};
	}
	Collision2DPoints Physics2D::GetCircleQuadCollisionPoints(const CircleCollider2D& c, const QuadCollider2D& q)
	{
		return {};
	}
	Collision2DPoints Physics2D::GetCirclePolygonCollisionPoints(const CircleCollider2D& c, const PolygonCollider2D& p)
	{
		return {};
	}

	Collision2DPoints Physics2D::GetLineLineCollisionPoints(const LineCollider2D& l1, const LineCollider2D& l2)
	{
		return {};
	}
	Collision2DPoints Physics2D::GetLineQuadCollisionPoints(const LineCollider2D& l, const QuadCollider2D& q)
	{

		return {};
	}
	Collision2DPoints Physics2D::GetLinePolygonCollisionPoints(const LineCollider2D& l, const PolygonCollider2D& p)
	{
		return {};
	}

	Collision2DPoints Physics2D::GetQuadQuadCollisionPoints(const QuadCollider2D& q1, const QuadCollider2D& q2)
	{
		GJKResult result = GJK(q1, q2);

		Collision2DPoints points;
		points.collide = result.collide;
		return points;

	}
	Collision2DPoints Physics2D::GetQuadPolygonCollisionPoints(const QuadCollider2D& q, const PolygonCollider2D& p)
	{
		return {};
	}

	Collision2DPoints Physics2D::GetPolygonPolygonCollisionPoints(
		const PolygonCollider2D& p1, const PolygonCollider2D& p2
	)
	{
		return {};
	}
} // namespace Orbital
