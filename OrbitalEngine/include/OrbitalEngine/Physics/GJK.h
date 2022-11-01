#pragma once

#include "OrbitalEngine/Components/ColliderComponent.h"
namespace Orbital
{
	struct GJKResult
	{
		bool collide = false;
	};

	static GJKResult GJK(Collider2DComponent col2, Collider2DComponent col1)
	{
		GJKResult result;
		std::vector<Maths::Vec2> geometry1 = col1.getGeometry();
		std::vector<Maths::Vec2> geometry2 = col2.getGeometry();

		return result;
	}
}
