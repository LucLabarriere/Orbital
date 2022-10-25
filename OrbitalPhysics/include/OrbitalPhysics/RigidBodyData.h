#pragma once

#include "OrbitalTools/Maths.h"

namespace Orbital
{
	struct RigidBodyData
	{
		Maths::Vec3 Position = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 Velocity = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 Torque = { 0.0f, 0.0f, 0.0f };
		bool Gravity = false;
		bool Collide = true;
		float Mass = 1.0f;
		float MomentsOfInertia = 1.0f;
		float Width = 1.0f;
		float Height = 1.0f;
	};
} // namespace Orbital
