#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalInputs/Event.h"
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

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        mHighRenderer.initialize();
        initializeInputManager();

        // Initializing services
        mServices.window = &mHighRenderer.getWindow();
        mServices.renderer = &mHighRenderer;
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
        mServices.renderer->terminate();
    }

    bool OrbitalApplication::onKeyPressed(KeyPressedEvent& e)
    {
        Logger::Debug("KeyPressed! ", e.getKey());

        return true;
    }

    bool OrbitalApplication::onMouseMove(MouseMoveEvent& e)
    {
        Logger::Debug("Mouse moved: ", e.getX(), " ", e.getY());
        return true;
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
