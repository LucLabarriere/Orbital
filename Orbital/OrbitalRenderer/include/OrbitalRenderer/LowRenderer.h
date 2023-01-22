#pragma once

#include "OrbitalRenderer/IndexBuffer.h"
#include "OrbitalRenderer/VertexArray.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Pointers.h"

namespace Orbital
{
	class Window;

	class ORBITAL_RENDERER_API LowRenderer
	{
	public:
		LowRenderer() = default;
		virtual ~LowRenderer() = default;

		auto initialize(unsigned int windowWidth, unsigned int windowHeight)
			-> Option<Error>;
		void terminate();
		void render(const VertexArray& vao, const IndexBuffer& ibo);
		void resetDrawCalls() { mDrawCalls = 0; }

		[[nodiscard]] auto getWindow() -> UniqueHandle<Window>;
		[[nodiscard]] auto getDrawCalls() const -> unsigned int;

	private:
		Unique<Window> mWindow = nullptr;
		unsigned int mDrawCalls = 0;
	};
} // namespace Orbital
