#include "OpenGLShader.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Containers.h"

namespace Orbital
{
    static std::unordered_map<GLuint, const char*> ShaderTypes = {
        { GL_VERTEX_SHADER, "Vertex Shader"},
        { GL_FRAGMENT_SHADER, "Fragment Shader"}
    };

    Shader* Shader::Create(const char* vsSource, const char* fsSource)
    {
        return new OpenGLShader(vsSource, fsSource);
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
        {
            GLint logSize = 0;
            glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
            GLchar* logMessage[logSize];
            glad_glGetShaderInfoLog(shader, logSize, &logSize, logMessage[0]);
            Logger::Error("Error in ", ShaderTypes[shaderType]);
            Logger::Error(logMessage);
        }

        return shader;
    }

    OpenGLShader::OpenGLShader(const char* vsSource, const char* fsSource)
        : Shader()
    {
        GLuint vertexShader = CompileShader(vsSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = CompileShader(fsSource, GL_FRAGMENT_SHADER);

        unsigned int shaderProgram;
        shaderProgram = glad_glCreateProgram();

        glad_glAttachShader(shaderProgram, vertexShader);
        glad_glAttachShader(shaderProgram, fragmentShader);
        glad_glLinkProgram(shaderProgram);

        char infoLog[512];
        int success;
        glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            Logger::Error("ERROR::PROGRAM::COMPILATION_FAILED");
        }
        glad_glUseProgram(shaderProgram);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);  
    }

    void OpenGLShader::bind() const
    {

    }
}
