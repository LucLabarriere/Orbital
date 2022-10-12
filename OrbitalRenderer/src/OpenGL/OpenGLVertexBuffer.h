#pragma once

#include "OrbitalRenderer/VertexBuffer.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(size_t bufferSize, size_t vertexSize, const void* data);
        virtual ~OpenGLVertexBuffer() override;

        virtual void addVertexAttribute(size_t componentCount, size_t attributeSize) override;
        virtual void bind() const override;

    private:
        GLuint mRendererID = 0;
        GLuint mVertexAttributeCount = 0;
        GLuint mVertexSize = 0;
        size_t mStride = 0;
    };
}
