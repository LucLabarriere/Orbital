#pragma once

#include "OrbitalEngine/Components/RigidBodyComponent.h"

namespace Orbital
{
	struct RigidBody2D : public RigidBodyComponent
	{
		Maths::Vec2 velocity = { 0.0f, 0.0f };
		Maths::Vec2 force = { 0.0f, 0.0f };

		static Maths::Vec2 GravityForce()
		{
			return { 0.0f, -9.81f };
		}
		static Maths::Vec2 NullForce()
		{
			return { 0.0f, 0.0f };
		}

		RigidBody2D(const TransformHandle& t) : RigidBodyComponent(t)
		{
		}
	};

	using RigidBody2DHandle = ComponentHandle<RigidBody2D>;
} // namespace Orbital
