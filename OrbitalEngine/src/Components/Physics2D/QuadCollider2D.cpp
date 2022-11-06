#include "OrbitalEngine/Components/Physics2D/QuadCollider2D.h"
#include "OrbitalEngine/Physics/PhysicsCalculations.h"

namespace Orbital
{
	QuadCollider2D::QuadCollider2D(const TransformHandle& transform, const RigidBody2DHandle& body)
		: Collider2DComponent(transform, body)
	{
	}

	std::vector<Maths::Vec2> QuadCollider2D::getGeometry() const
	{
		Maths::Mat4 model = mTransform->getModelMatrix();
		std::vector<Maths::Vec2> points(4);
		for (auto& point : points)
		{
		}
		return points;
	}

	Collision2DPoints QuadCollider2D::getCollisionPoints(const Collider2DComponent& other) const
	{
		return other.getCollisionPoints(*this);
	}

	Collision2DPoints QuadCollider2D::getCollisionPoints(const LineCollider2D& other) const
	{
		return Physics2D::GetLineQuadCollisionPoints(other, *this);
	}

	Collision2DPoints QuadCollider2D::getCollisionPoints(const CircleCollider2D& other) const
	{
		return Physics2D::GetCircleQuadCollisionPoints(other, *this);
	}

	Collision2DPoints QuadCollider2D::getCollisionPoints(const QuadCollider2D& other) const
	{
		return Physics2D::GetQuadQuadCollisionPoints(*this, other);
	}

	Collision2DPoints QuadCollider2D::getCollisionPoints(const PolygonCollider2D& other) const
	{
		return Physics2D::GetQuadPolygonCollisionPoints(*this, other);
	}
} // namespace Orbital



/*
 * In transform, store the model matrix and update it when needed = interact with the object using move, rotate, scale and setters (then request update)
 * In Collider : keep the transform + the mesh filter component.
 * this way, the mesh informations can be used in the collider
 *
 * Meshes to handle: Quad (just 2 triangles for GJK), Triangles, Cubes, Spheres : think about how to make it work with GJK
 *
 *
 * In Mesh Renderer : reference the mesh filter
 * */
