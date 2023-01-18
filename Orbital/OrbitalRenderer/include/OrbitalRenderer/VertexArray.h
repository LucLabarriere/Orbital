#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API VertexArray
	{
	public:
		static auto Create() -> VertexArray*;

		virtual ~VertexArray() = default;

		virtual auto bind() const -> void = 0;
	};
} // namespace Orbital
