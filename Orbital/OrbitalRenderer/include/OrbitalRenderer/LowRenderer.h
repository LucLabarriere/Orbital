#pragma once

#include "OrbitalRenderer/IndexBuffer.h"
#include "OrbitalRenderer/VertexArray.h"

namespace Orbital
{
	class Window;

	class ORENDERER_API LowRenderer
	{
	public:
		LowRenderer();
		LowRenderer(LowRenderer&&) = delete;
		LowRenderer(const LowRenderer&) = delete;
		LowRenderer& operator=(LowRenderer&&) = delete;
		LowRenderer& operator=(const LowRenderer&) = delete;
		virtual ~LowRenderer();

		Window& getWindow()
		{
			return *mWindow;
		}

		void initialize(unsigned int windowWidth, unsigned int windowHeight);
		void terminate();
		void render(const VertexArray& vao, const IndexBuffer& ibo) const;

	private:
		Window* mWindow;
	};
} // namespace Orbital
