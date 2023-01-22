#include "OpenGLIndexBuffer.h"

namespace Orbital
{
	auto IndexBuffer::Create(size_t bufferSize, size_t indexCount, const void* data)
		-> IndexBuffer*
	{
		return new OpenGLIndexBuffer(bufferSize, indexCount, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(
		size_t bufferSize, size_t indexCount, const void* data
	)
		: IndexBuffer(indexCount)
	{
		glad_glGenBuffers(1, &mRendererID);
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glad_glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, (GLuint)bufferSize, data, GL_STATIC_DRAW
		);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glad_glDeleteBuffers(1, &mRendererID);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	}
} // namespace Orbital
