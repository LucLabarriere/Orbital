#include "OrbitalRenderer/Window.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    Window::Window() 
    {
        Orbital::Logger::Log("Initializing GLFW");

        if (!glfwInit())
        {
            Orbital::Logger::Error("Error while initializing GLFW");
            __builtin_trap(); 
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        Orbital::Logger::Log("Creating the window");

        mGLFWwindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!mGLFWwindow)
        {
            Orbital::Logger::Error("Error while creating the GLFW window");
            glfwTerminate();
            __builtin_trap();
        }   

        glfwMakeContextCurrent(mGLFWwindow);

        int version = gladLoadGL(glfwGetProcAddress);

        Logger::Log("GLAD Version  ", GLAD_VERSION_MAJOR(version), ".", GLAD_VERSION_MINOR(version));
        // printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

        Orbital::Logger::Log("Setting GL context");

        /* Make the window's context current */

        /* Loop until the user closes the window */
        Orbital::Logger::Log("Looping...");
        while (!glfwWindowShouldClose(mGLFWwindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(mGLFWwindow);
   

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }

}
