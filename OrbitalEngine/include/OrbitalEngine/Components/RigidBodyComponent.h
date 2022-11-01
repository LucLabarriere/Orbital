#pragma once

#include "TransformComponent.h"

namespace Orbital
{
	enum class BodyType
	{
		Static = 0,
		Kinetimatic,
		Dynamic
	};

	struct RigidBodyComponent
	{
		TransformHandle transform;
		float mass = 1.0f;
		bool gravity = true;

		RigidBodyComponent(const TransformHandle& t) : transform(t)
		{
		}
	};
} // namespace Orbital
