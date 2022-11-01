#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	enum class MeshType 
	{
		Triangle = 0,
		Quad,
		Cube,
		Sphere
	};

	struct MeshFilter
	{
		MeshType mesh;

		MeshFilter(MeshType m) : mesh(m)
		{
		}
	};

	using MeshFilterHandle = ComponentHandle<MeshFilter>;
} // namespace Orbital
