#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    class ORENDERER_API Shader
    {
    public:
        static Shader* Create(const char* vsSource, const char* fsSource);
        virtual ~Shader() { }

        virtual void bind() const = 0;
    };
}
