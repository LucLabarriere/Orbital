#include "OrbitalEngine/Components/Physics3D/SphereCollider3D.h"
#include "OrbitalEngine/Physics/PhysicsCalculations.h"

namespace Orbital
{
	SphereCollider3D::SphereCollider3D(const TransformHandle& transform, const RigidBody3DHandle& body)
		: Collider3DComponent(transform, body)
	{
	}

	Collision3DPoints SphereCollider3D::getCollisionPoints(const Collider3DComponent& other) const
	{
		return other.getCollisionPoints(*this);
	}

	Collision3DPoints SphereCollider3D::getCollisionPoints(const PlaneCollider3D& other) const
	{
		return Physics3D::GetPlaneSphereCollisionPoints(other, *this);
	}

	Collision3DPoints SphereCollider3D::getCollisionPoints(const SphereCollider3D& other) const
	{
		return Physics3D::GetSphereSphereCollisionPoints(*this, other);
	}

	Collision3DPoints SphereCollider3D::getCollisionPoints(const BoxCollider3D& other) const
	{
		return Physics3D::GetSphereBoxCollisionPoints(*this, other);
	}
} // namespace Orbital
