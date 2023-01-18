#pragma once

#include "OrbitalRenderer/IndexBuffer.h"
#include "OrbitalRenderer/VertexArray.h"

namespace Orbital
{
	class Window;

	class ORBITAL_RENDERER_API LowRenderer
	{
	public:
		LowRenderer();
		LowRenderer(LowRenderer&&) = delete;
		LowRenderer(const LowRenderer&) = delete;
		virtual ~LowRenderer();

		auto getWindow() -> Window&;

		void initialize(unsigned int windowWidth, unsigned int windowHeight);
		void terminate();
		void render(const VertexArray& vao, const IndexBuffer& ibo);
		void resetDrawCalls() { mDrawCalls = 0; }

		[[nodiscard]] auto getDrawCalls() const -> unsigned int;

	private:
		Window* mWindow;
		unsigned int mDrawCalls = 0;
	};
} // namespace Orbital
