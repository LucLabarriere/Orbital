#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    class ORENDERER_API VertexArray
    {
    public:
        static VertexArray* Create();
        virtual ~VertexArray() { };

        virtual void bind() const = 0;
    };
}
