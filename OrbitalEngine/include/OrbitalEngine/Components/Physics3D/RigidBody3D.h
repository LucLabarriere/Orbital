#pragma once

#include "OrbitalEngine/Components/RigidBodyComponent.h"

namespace Orbital
{
	struct RigidBody3D : public RigidBodyComponent
	{
		Maths::Vec3 velocity = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 force = { 0.0f, 0.0f, 0.0f };

		static Maths::Vec3 GravityForce()
		{
			return { 0.0f, -9.81f, 0.0f };
		}
		static Maths::Vec3 NullForce()
		{
			return { 0.0f, 0.0f, 0.0f };
		}

		RigidBody3D(const TransformHandle& t) : RigidBodyComponent(t)
		{
		}
	};

	using RigidBody3DHandle = ComponentHandle<RigidBody3D>;
} // namespace Orbital
