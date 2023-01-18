#pragma once

#include "OrbitalRenderer/RendererContext.h"
#include "OrbitalRenderer/VertexArray.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		auto bind() const -> void override;

	private:
		GLuint mRendererID = 0;
	};
} // namespace Orbital
