#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    class ORENDERER_API VertexBuffer
    {
    public:
        static VertexBuffer* Create(size_t bufferSize, size_t vertexSize, const void* data);
        virtual ~VertexBuffer() { }

        virtual void addVertexAttribute(size_t componentCount, size_t attributeSize) = 0;
        virtual void bind() const = 0;
    };
}
