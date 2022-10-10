#ifdef ORENDERER_OPENGL

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    void _post_call_callback_default(const char *name, void *funcptr, int len_args, ...) {
        GLenum error_code;
        error_code = glad_glGetError();
        if (error_code != GL_NO_ERROR && funcptr == (void*)glEnable /* or strcmp(name,"glError") == 0*/) {
            va_list ap;
            va_start(ap, len_args);
            GLenum arg0 = va_arg(ap, GLenum);
            va_end(ap);
            printf("Called glError(%d) with Error %d\n", arg0, error_code);
        }
    }

    void glfwErrorCallback(int code, const char* description)
    {
        Logger::Error("GLFW: [", code, "] ", description);
    }

    void RenderAPI::Initialize()
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

    }

    void RenderAPI::Terminate()
    {
        Logger::Log("Terminating OpenGL API");
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
