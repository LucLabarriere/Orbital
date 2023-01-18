#pragma once

#include "OrbitalRenderer/RendererContext.h"
#include "OrbitalRenderer/VertexBuffer.h"

namespace Orbital
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t bufferSize, size_t vertexSize, const void* data);
		~OpenGLVertexBuffer() override;

		auto addVertexAttribute(size_t componentCount, size_t attributeSize) ->void override;
		auto bind() const ->void override;

	private:
		GLuint mRendererID = 0;
		GLuint mVertexAttributeCount = 0;
		GLuint mVertexSize = 0;
		size_t mStride = 0;
	};
} // namespace Orbital
