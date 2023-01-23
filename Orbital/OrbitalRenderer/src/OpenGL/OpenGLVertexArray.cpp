#include "OpenGLVertexArray.h"

namespace Orbital
{
	auto VertexArray::Create() -> VertexArray*
	{
		return new OpenGLVertexArray;
	}

	OpenGLVertexArray::OpenGLVertexArray() : VertexArray()
	{
		glad_glGenVertexArrays(1, &mRendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glad_glDeleteVertexArrays(1, &mRendererID);
	}

	auto OpenGLVertexArray::bind() const -> void
	{
		glad_glBindVertexArray(mRendererID);
	}
} // namespace Orbital
