#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API IndexBuffer
	{
	public:
		static auto Create(size_t bufferSize, size_t indexCount, const void* data)
			-> IndexBuffer*;

		IndexBuffer(size_t indexCount) : mIndexCount(indexCount){};
		virtual ~IndexBuffer() = default;

		[[nodiscard]] virtual auto getIndexCount() const -> unsigned int
		{
			return mIndexCount;
		}
		virtual auto bind() const -> void = 0;

	protected:
		unsigned int mIndexCount = 0;
	};
} // namespace Orbital
