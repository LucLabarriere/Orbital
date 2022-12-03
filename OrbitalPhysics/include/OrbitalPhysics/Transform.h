#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics
	{
		struct Transform
		{
			Maths::Vec3 position = { 0.0f, 0.0f, 0.0f };
			Maths::Vec3 rotation = { 0.0f, 0.0f, 0.0f };
			Maths::Vec3 scale = { 1.0f, 1.0f, 1.0f };

			Maths::Mat4 getModelMatrix() const
			{
				Maths::Mat4 model(1.0f);

				model = Maths::Translate(model, position);
				model = Maths::Rotate(model, rotation.x, { 1.0f, 0.0f, 0.0f });
				model = Maths::Rotate(model, rotation.y, { 0.0f, 1.0f, 0.0f });
				model = Maths::Rotate(model, rotation.z, { 0.0f, 0.0f, 1.0f });
				model = Maths::Scale(model, scale);

				return model;
			}
		};
	} // namespace Physics
} // namespace Orbital
