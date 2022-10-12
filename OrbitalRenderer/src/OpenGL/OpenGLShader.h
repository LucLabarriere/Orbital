#pragma once

#include "OrbitalRenderer/Shader.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    class ORENDERER_API OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* vsSource, const char* fsSource);
        virtual ~OpenGLShader() override;
    
        virtual void bind() const override;

    private:
        GLuint mRendererID = 0;
    };
}
