#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics
	{
		struct ORBITAL_PHYSICS_API Transform
		{
			Maths::Vec3 position = { 0.0f, 0.0f, 0.0f };
			Maths::Vec3 rotation = { 0.0f, 0.0f, 0.0f };
			Maths::Vec3 scale = { 1.0f, 1.0f, 1.0f };

			auto getModelMatrix() const -> Maths::Mat4;
		};
	} // namespace Physics
} // namespace Orbital
