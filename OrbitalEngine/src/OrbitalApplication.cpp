#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
        : mHighRenderer()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {

    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        mHighRenderer.initialize();

        // Initializing services
        mServices.window = &mHighRenderer.getWindow();
        mServices.renderer = &mHighRenderer;
    }

    void OrbitalApplication::terminate()
    {
        mServices.renderer->terminate();
        Logger::Log("Terminating application");
    }

    int OrbitalApplication::run()
    {
        initialize();
        Orbital::Logger::Log("Looping...");

        while (!mServices.window->shouldClose())
        {
            RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderAPI::Clear();

            mServices.renderer->drawQuad();
            update();

            mServices.window->swapBuffers();
            RenderAPI::PoolEvents();
        }

        terminate();
        return 0;
    }
}
