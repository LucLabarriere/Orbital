#pragma once

#include "OrbitalRenderer/Context.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalRenderer/Containers.h"

namespace Orbital
{
    class ORENDERER_API Shader
    {
    public:

        static Shader* Create(const char* vsSource, const char* fsSource);
        virtual ~Shader() { }

        virtual void bind() const = 0;
        virtual unsigned int getUniformLocation(const std::string& uniformName) const = 0;

        virtual void setUniform1ui(unsigned int uniformLocation, unsigned int value) const = 0;
        virtual void setUniform1f(unsigned int uniformLocation, float value) const = 0;
        virtual void setUniform2f(unsigned int uniformLocation, const Maths::Vec2& vec) const = 0;
        virtual void setUniform3f(unsigned int uniformLocation, const Maths::Vec3& vec) const = 0;
        virtual void setUniform4f(unsigned int uniformLocation, const Maths::Vec4& vec) const = 0;
        virtual void setUniformMat4f(unsigned int uniformLocation, const Maths::Mat4& mat) const = 0;
    };
}

