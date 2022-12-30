#include "OpenGLVertexArray.h"

namespace Orbital
{
    VertexArray* VertexArray::Create()
    {
        return new OpenGLVertexArray;
    }

    OpenGLVertexArray::OpenGLVertexArray()
        : VertexArray()
    {
        glad_glGenVertexArrays(1, &mRendererID);
    }

    void OpenGLVertexArray::bind() const
    {
        glad_glBindVertexArray(mRendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glad_glDeleteVertexArrays(1, &mRendererID);
    }
}
