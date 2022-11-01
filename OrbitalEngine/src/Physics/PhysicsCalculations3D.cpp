#include "OrbitalEngine/Physics/PhysicsCalculations.h"
#include "OrbitalEngine/Components/Physics3D/Colliders3D.h"

namespace Orbital
{
	Collision3DPoints Physics3D::GetPlanePlaneCollisionPoints(const PlaneCollider3D& p1, const PlaneCollider3D& p2)
	{
		return {};
	}

	Collision3DPoints Physics3D::GetPlaneSphereCollisionPoints(const PlaneCollider3D& p, const SphereCollider3D& s)
	{
		Maths::Vec3 diffVector = s.getTransform()->position - p.getTransform()->position;
		float projection = Maths::Dot(diffVector, p.getNormal());
		float distance = Maths::Absolute(projection);
		float penetrationDistance = s.getRadius() - distance;

		return {
			.A = p.getTransform()->position,
			.B = s.getTransform()->position,
			.penetrationVector = p.getNormal() * penetrationDistance,
			.normal = p.getNormal(),
			.penetrationDistance = penetrationDistance,
			.collide = (penetrationDistance > 0 ? true : false),
		};
	}

	Collision3DPoints Physics3D::GetPlaneBoxCollisionPoints(const PlaneCollider3D& p, const BoxCollider3D& b)
	{
		return {};
	}

	Collision3DPoints Physics3D::GetSphereSphereCollisionPoints(const SphereCollider3D& s1, const SphereCollider3D& s2)
	{
		Maths::Vec3 vector = s2.getTransform()->position - s1.getTransform()->position;
		float distance = Maths::Magnitude(vector);
		Maths::Vec3 normal = vector / distance;
		float penetrationDistance = s1.getRadius() + s2.getRadius() - distance;
		Maths::Vec3 penetrationVector = penetrationDistance * normal;

		return {
			.A = s1.getTransform()->position,
			.B = s2.getTransform()->position,
			.penetrationVector = penetrationVector,
			.normal = normal,
			.penetrationDistance = penetrationDistance,
			.collide = (penetrationDistance > 0.0f ? true : false),
		};
	}

	Collision3DPoints Physics3D::GetSphereBoxCollisionPoints(const SphereCollider3D& s, const BoxCollider3D& b)
	{
		return {};
	}

	Collision3DPoints Physics3D::GetBoxBoxCollisionPoints(const BoxCollider3D& b1, const BoxCollider3D& b2)
	{
		return {};
	}
} // namespace Orbital
