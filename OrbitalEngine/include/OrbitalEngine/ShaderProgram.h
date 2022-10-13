#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalRenderer/Shader.h"

namespace Orbital
{
    enum Uniform 
    {
        Model = 0
    };
        
    class OENGINE_API ShaderProgram
    {
    public:

        using UniformLocationMap = std::unordered_map<Uniform, unsigned int>;

    public:
        ShaderProgram();
        ~ShaderProgram();

        void initialize();
        void bind() const;
        void mapUniformLocation(Uniform uniform, const std::string& uniformName);
    
        template <typename T>
        void setUniform(Uniform uniform, const T& value);

    private:
        Shader* mShader = nullptr;
        UniformLocationMap mUniformLocations;
    };

    template<> // Unsigned int
    inline void ShaderProgram::setUniform<unsigned int>(Uniform uniform, const unsigned int& value)
    {
        mShader->setUniform1ui(mUniformLocations[uniform], value);
    }

    template<> // Float
    inline void ShaderProgram::setUniform<float>(Uniform uniform, const float& value)
    {
        mShader->setUniform1f(mUniformLocations[uniform], value);
    }
    
    template<> //  Vec2
    inline void ShaderProgram::setUniform<Maths::Vec2>(Uniform uniform, const Maths::Vec2& value)
    {
        mShader->setUniform2f(mUniformLocations[uniform], value);
    }

    template<> // Vec3
    inline void ShaderProgram::setUniform<Maths::Vec3>(Uniform uniform, const Maths::Vec3& value)
    {
        mShader->setUniform3f(mUniformLocations[uniform], value);
    }

    template<> // Vec4
    inline void ShaderProgram::setUniform<Maths::Vec4>(Uniform uniform, const Maths::Vec4& value)
    {
        mShader->setUniform4f(mUniformLocations[uniform], value);
    }

    template<> // Mat4
    inline void ShaderProgram::setUniform<Maths::Mat4>(Uniform uniform, const Maths::Mat4& value)
    {
        mShader->setUniformMat4f(mUniformLocations[uniform], value);
    }
}
