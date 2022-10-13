#include "OpenGLShader.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Containers.h"

namespace Orbital
{ 
    static std::unordered_map<GLuint, const char*> LogTypes = {
        { GL_VERTEX_SHADER, "Vertex Shader"},
        { GL_FRAGMENT_SHADER, "Fragment Shader"},
        { GL_LINK_STATUS, "Shader linking"}
    };

    Shader* Shader::Create(const char* vsSource, const char* fsSource)
    {
        return new OpenGLShader(vsSource, fsSource);
    }

    static void LogShaderInfo(GLuint shader, GLuint logType)
    {
        GLint logSize = 0;
        glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* logMessage[logSize];
        glad_glGetShaderInfoLog(shader, logSize, &logSize, logMessage[0]);
        Logger::Error("Error ", LogTypes[logType]);
        Logger::Error(logMessage);
    }

    static GLuint CompileShader(const char* source, GLuint shaderType)
    {
        GLuint shader;
        shader = glad_glCreateShader(shaderType);

        glad_glShaderSource(shader, 1, &source, NULL);
        glad_glCompileShader(shader);

        GLint success;
        glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success)
            LogShaderInfo(shader, shaderType);
        
        return shader;
    }

    OpenGLShader::OpenGLShader(const char* vsSource, const char* fsSource)
        : Shader()
    {
        GLuint vertexShader = CompileShader(vsSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = CompileShader(fsSource, GL_FRAGMENT_SHADER);

        mRendererID = glad_glCreateProgram();

        glad_glAttachShader(mRendererID, vertexShader);
        glad_glAttachShader(mRendererID, fragmentShader);
        glad_glLinkProgram(mRendererID);

        int success;

        glad_glGetProgramiv(mRendererID, GL_LINK_STATUS, &success);

        if(!success)
            LogShaderInfo(mRendererID, GL_LINK_STATUS);
        else
            glad_glUseProgram(mRendererID);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glad_glDeleteProgram(mRendererID);
    }

    void OpenGLShader::bind() const
    {
        glad_glUseProgram(mRendererID);
    }


    unsigned int OpenGLShader::getUniformLocation(const std::string& uniformName) const
    {
        return glad_glGetUniformLocation(mRendererID, uniformName.data());
    }

    void OpenGLShader::setUniform1ui(unsigned int uniformLocation, unsigned int value) const
    {
        glad_glUniform1ui(uniformLocation, value);
    }

    void OpenGLShader::setUniform1f(unsigned int uniformLocation, float value) const
    {
        glad_glUniform1f(uniformLocation, value);
    }

    void OpenGLShader::setUniform2f(unsigned int uniformLocation, const Maths::Vec2& vec) const
    {
        glad_glUniform2f(uniformLocation, vec[0], vec[1]);
    }

    void OpenGLShader::setUniform3f(unsigned int uniformLocation, const Maths::Vec3& vec) const
    {
        glad_glUniform3f(uniformLocation, vec[0], vec[1], vec[2]);
    }

    void OpenGLShader::setUniform4f(unsigned int uniformLocation, const Maths::Vec4& vec) const
    {
        glad_glUniform4f(uniformLocation, vec[0], vec[1], vec[2], vec[3]);
    }

    void OpenGLShader::setUniformMat4f(unsigned int uniformLocation, const Maths::Mat4& mat) const
    {
        glad_glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
    }
}
