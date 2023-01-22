#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API VertexBuffer
	{
	public:
		static auto Create(size_t bufferSize, size_t vertexSize, const void* data)
			-> VertexBuffer*;

		virtual ~VertexBuffer() = default;

		virtual auto addVertexAttribute(size_t componentCount, size_t attributeSize)
			-> void = 0;
		virtual auto bind() const -> void = 0;
	};
} // namespace Orbital
