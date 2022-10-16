#pragma once

#include "OrbitalRenderer/IndexBuffer.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(size_t bufferSize, size_t indexCount, const void* data);
        virtual ~OpenGLIndexBuffer() override;

        virtual void bind() const override;

    private:
        GLuint mRendererID = 0;
    };
}
