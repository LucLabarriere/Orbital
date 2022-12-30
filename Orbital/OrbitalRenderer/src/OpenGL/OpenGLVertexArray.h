#pragma once

#include "OrbitalRenderer/VertexArray.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    class ORENDERER_API OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;

        virtual void bind() const override;
        
    private:
        GLuint mRendererID = 0;
    };
}
