#include "OpenGL/OpenGLWindow.h"
#include "GLFW/glfw3.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/RenderAPI.h"
#include <unordered_map>
#include <vector>
#include <unordered_set>

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

    void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
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

    Window* Window::Create()
    {
        return new OpenGLWindow;
    }

    OpenGLWindow::OpenGLWindow() 
    {

    }
    
    void OpenGLWindow::swapBuffers()
    {
        glfwSwapBuffers(mGLFWwindow);
    }

    bool OpenGLWindow::initialize()
    {
        Orbital::Logger::Log("Creating the window");
        
        mGLFWwindow = glfwCreateWindow(640, 480, "Orbital", NULL, NULL);
        if (!mGLFWwindow)
        {
            Orbital::Logger::Error("Error while creating the GLFW window");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(mGLFWwindow);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return false;
        }

        int context_flags = 0;
        glad_glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
        if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            Logger::Log("Debug context created");
            glad_glEnable(GL_DEBUG_OUTPUT);
            glad_glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glad_glDebugMessageCallback(glDebugOutput, NULL);
            glad_glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        }

        Orbital::Logger::Log("Setting GL context");
        Orbital::Logger::Log("GL   version: ", glad_glGetString(GL_VERSION));
        Orbital::Logger::Log("GLSL version: ", glad_glGetString(GL_SHADING_LANGUAGE_VERSION));

        /* Loop until the user closes the window */
        Orbital::Logger::Log("Looping...");
        while (!shouldClose())
        {
            /* Render here */
            RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderAPI::Clear();

            swapBuffers();

            /* Poll for and process events */
            RenderAPI::PoolEvents();
        }

        RenderAPI::Terminate();
        return true;
    }

    bool OpenGLWindow::shouldClose() const
    {
        return glfwWindowShouldClose(mGLFWwindow);
    }
}
