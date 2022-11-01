#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/Physics3D/RigidBody3D.h"

namespace Orbital
{
	class OENGINE_API BoxCollider3D : public Collider3DComponent
	{
	public:
		BoxCollider3D(const TransformHandle& transform, const RigidBody3DHandle& dynamics);

		virtual Collision3DPoints getCollisionPoints(const Collider3DComponent& other) const override;
		virtual Collision3DPoints getCollisionPoints(const PlaneCollider3D& other) const override;
		virtual Collision3DPoints getCollisionPoints(const SphereCollider3D& other) const override;
		virtual Collision3DPoints getCollisionPoints(const BoxCollider3D& other) const override;
	};
} // namespace Orbital
