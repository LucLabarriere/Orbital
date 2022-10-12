#ifdef ORENDERER_OPENGL

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/Containers.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    static std::unordered_map<GLenum, const std::string>  sources = {
        { GL_DEBUG_SOURCE_API,              "GL" },
        { GL_DEBUG_SOURCE_WINDOW_SYSTEM,    "Window" },
        { GL_DEBUG_SOURCE_THIRD_PARTY,      "Third party" },
        { GL_DEBUG_SOURCE_APPLICATION,      "App" },
        { GL_DEBUG_SOURCE_OTHER,            "Other" }
    };

    static std::unordered_map<GLenum, const std::string>  types = {
        { GL_DEBUG_TYPE_ERROR,              "GL Type" },
        { GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,"Deprecated" },
        { GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined behaviour" },
        { GL_DEBUG_TYPE_PORTABILITY,        "Not portable" },
        { GL_DEBUG_TYPE_PERFORMANCE,        "Bad performances" },
        { GL_DEBUG_TYPE_MARKER,             "Note" },
        { GL_DEBUG_TYPE_PUSH_GROUP,         "Debug push" },
        { GL_DEBUG_TYPE_POP_GROUP,          "Debug pop" },
        { GL_DEBUG_TYPE_OTHER,              "Other" },
    };

    static std::unordered_map<GLenum, const std::string>  severities = {
        { GL_DEBUG_SEVERITY_HIGH,           "HIGH" },
        { GL_DEBUG_SEVERITY_MEDIUM,         "MEDIUM" },
        { GL_DEBUG_SEVERITY_LOW,            "LOW" },
        { GL_DEBUG_SEVERITY_NOTIFICATION,   "NOTIFICATION" }
    };

    void OpenGLDebugOutput(
            GLenum source, GLenum type, unsigned int id,
            GLenum severity, GLsizei length, const char *message,
            const void *userParam)
    {
        std::unordered_set<GLenum> errors = { GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM, GL_DEBUG_SEVERITY_LOW };
        bool isError = false;
        if (errors.find(severity) != errors.end())
        {
            isError = true;
        }

        std::string toPrint = "[" + severities[severity] + "] from " + sources[source] + ": '" + types[type] + "'";

        if (isError)
        {
            Logger::Error(toPrint + "\n" + message);
        }
        else
        {
            Logger::Log(toPrint + "\n" + message);
        }
    }

    void glfwErrorCallback(int code, const char* description)
    {
        Logger::Error("GLFW: [", code, "] ", description);
    }

    bool RenderAPI::Initialize()
    {
        Logger::Log("Initializing OpenGL API");
        Orbital::Logger::Log("Initializing GLFW");

        assert(glfwInit());

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        Logger::Log("GLFW: ", major, ".", minor, ".",  revision);

        glfwSetErrorCallback(glfwErrorCallback);
      
        #ifdef ORENDERER_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        #endif

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        Logger::Log("GLFW: ", glfwGetVersionString());
        return true;
    }

    bool RenderAPI::LateInitialize()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        {
            Logger::Critical("Failed to initialize OpenGL context");
            return false;
        }

        int context_flags = 0;
        glad_glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
        if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            Logger::Debug("Debug context created");
            glad_glEnable(GL_DEBUG_OUTPUT);
            glad_glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glad_glDebugMessageCallback(OpenGLDebugOutput, NULL);
            glad_glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        }

        Orbital::Logger::Log("Setting GL context");
        Orbital::Logger::Log("GL   version: ", glad_glGetString(GL_VERSION));
        Orbital::Logger::Log("GLSL version: ", glad_glGetString(GL_SHADING_LANGUAGE_VERSION));

        return true;
    }

    void RenderAPI::Terminate()
    {
        Logger::Log("Terminating OpenGL API");
        glfwTerminate();
    }

    void RenderAPI::DrawTriangles(size_t firstIndex, size_t vertexCount)
    {
        glad_glDrawArrays(GL_TRIANGLES, firstIndex, vertexCount);
    }

    void RenderAPI::Clear()
    {
        glad_glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void RenderAPI::ClearColor(float r, float g, float b, float a)
    {
        glad_glClearColor(r, g, b, a);
    }

    void RenderAPI::PoolEvents()
    {
        glfwPollEvents();
    }
}
#endif
