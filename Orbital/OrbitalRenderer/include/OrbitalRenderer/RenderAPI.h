#pragma once

#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/Errors.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API RenderAPI
	{
	public:
		static auto Initialize() -> Option<Error>;
		static auto LateInitialize() -> Option<Error>;
		static void Terminate();

		static void DrawTriangles(size_t firstIndex, size_t vertexCount);
		static void Clear();
		static auto ClearColor(float r, float g, float b, float a) -> void;

	private:
		static inline unsigned int mIBO = 0;
	};
} // namespace Orbital
