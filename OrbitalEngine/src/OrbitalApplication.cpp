#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/RenderAPI.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
        : mHighRenderer()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {

    }

    static void EventCallback(const std::string& message)
    {
        Logger::Debug(message);
    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        mHighRenderer.initialize();
        RenderAPI::SetEventCallback(&EventCallback);

        // Initializing services
        mServices.window = &mHighRenderer.getWindow();
        mServices.renderer = &mHighRenderer;
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
        mServices.renderer->terminate();
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
