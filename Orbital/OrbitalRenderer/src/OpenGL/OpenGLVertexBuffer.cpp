#include "OpenGLVertexBuffer.h"

namespace Orbital
{
	auto VertexBuffer::Create(size_t bufferSize, size_t vertexSize, const void* data) -> VertexBuffer* 
	{
		return new OpenGLVertexBuffer(bufferSize, vertexSize, data);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t bufferSize, size_t vertexSize, const void* data)
		: VertexBuffer(), mVertexSize(vertexSize)
	{
		glad_glGenBuffers(1, &mRendererID);
		glad_glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glad_glBufferData(GL_ARRAY_BUFFER, (GLuint)bufferSize, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glad_glDeleteBuffers(1, &mRendererID);
	}

	void OpenGLVertexBuffer::addVertexAttribute(size_t componentCount, size_t attributeSize)
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glad_glEnableVertexAttribArray(mVertexAttributeCount);
		glad_glVertexAttribPointer(
			mVertexAttributeCount, componentCount, GL_FLOAT, GL_FALSE, mVertexSize, (GLvoid*)mStride
		);

		mVertexAttributeCount++;
		mStride += attributeSize;
	}

	void OpenGLVertexBuffer::bind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	}
} // namespace Orbital
