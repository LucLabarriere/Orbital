#include "OrbitalEngine/Components/Physics3D/PlaneCollider3D.h"
#include "OrbitalEngine/Physics/PhysicsCalculations.h"

namespace Orbital
{
	PlaneCollider3D::PlaneCollider3D(const TransformHandle& transform, const RigidBody3DHandle& rb)
		: Collider3DComponent(transform, rb)
	{
	}

	Collision3DPoints PlaneCollider3D::getCollisionPoints(const Collider3DComponent& other) const
	{
		return other.getCollisionPoints(*this);
	}

	Collision3DPoints PlaneCollider3D::getCollisionPoints(const PlaneCollider3D& other) const
	{
		return Physics3D::GetPlanePlaneCollisionPoints(*this, other);
	}

	Collision3DPoints PlaneCollider3D::getCollisionPoints(const SphereCollider3D& other) const
	{
		return Physics3D::GetPlaneSphereCollisionPoints(*this, other);
	}

	Collision3DPoints PlaneCollider3D::getCollisionPoints(const BoxCollider3D& other) const
	{
		return Physics3D::GetPlaneBoxCollisionPoints(*this, other);
	}
} // namespace Orbital
