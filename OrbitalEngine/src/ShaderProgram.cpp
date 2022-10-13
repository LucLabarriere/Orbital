#include "OrbitalEngine/ShaderProgram.h"

namespace Orbital
{
    ShaderProgram::ShaderProgram()
    {

    }

    void ShaderProgram::initialize()
    {
        const char *vertexShaderSource = "#version 400 core\n"
            "layout (location = 0) in vec3 a_Position;\n"
            "layout (location = 1) in vec3 a_Color;\n"
            "uniform mat4 u_Model = mat4(1.0f);\n"
            "out vec4 v_Color;"
            "void main()\n"
            "{\n"
            "   gl_Position = u_Model * vec4(a_Position, 1.0);\n"
            "   v_Color = vec4(a_Color, 1.0);\n"
        "}\0";

        const char *fragmentShaderSource = "#version 400 core\n"
            "in vec4 v_Color;\n"
            "out vec4 o_Color;\n"
            "void main()\n"
            "{\n"
            "o_Color = v_Color;"
        "}\0";

        mShader = Shader::Create(vertexShaderSource, fragmentShaderSource);
        mShader->bind();
    }

    ShaderProgram::~ShaderProgram()
    {
        delete mShader;
    }

    void ShaderProgram::bind() const
    {
        mShader->bind();
    }

    void ShaderProgram::mapUniformLocation(Uniform uniform, const std::string& uniformName)
    {
        mUniformLocations[uniform] = mShader->getUniformLocation(uniformName);
    }
}
