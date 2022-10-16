#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    class IndexBuffer
    {
    public:
        IndexBuffer(size_t indexCount) : mIndexCount(indexCount) { }
        static IndexBuffer* Create(size_t bufferSize, size_t indexCount, const void* data);
        virtual ~IndexBuffer() { }

        virtual unsigned int getIndexCount() const { return mIndexCount; }
        virtual void bind() const = 0;

    protected:
        unsigned int mIndexCount = 0;
    };
}
