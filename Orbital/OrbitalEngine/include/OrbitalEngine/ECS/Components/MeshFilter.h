#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Handle.h"

namespace Orbital
{
	enum class MeshType
	{
		Triangle = 0,
		Quad,
		Cube,
		Sphere
	};

	/**
	 * @class MeshFilter
	 * @brief Describes a mesh
	 *
	 * Used by the MeshComponent and sometimes by the PhysicsComponent
	 *
	 * @todo Modify the components that depend on it when it is updated or use it at every function call
	 */
	struct MeshFilter : public Component
	{
		MeshType mesh;

		MeshFilter(const Component::InitArgs& c, const MeshType& m)
			: Component(c), mesh(m)
		{
		}
	};

	using MeshFilterHandle = SafeHandle<MeshFilter>;
} // namespace Orbital
