#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalTools/Maths.h"

namespace Orbital
{
	struct DynamicsComponent
	{
		TransformHandle transform;
		float mass = 1.0f;
		Maths::Vec3 velocity = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 force = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 friction = { 0.0f, 0.0f, 0.0f };
		bool gravity = true;

		DynamicsComponent(const TransformHandle& t) : transform(t)
		{
		}
	};

	using DynamicsHandle = ComponentHandle<DynamicsComponent>;
} // namespace Orbital
