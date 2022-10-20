#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
        : mHighRenderer(), mRegistry()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {
        LOGFUNC();
    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        mHighRenderer.initialize();
        mWindow = &mHighRenderer.getWindow();
        initializeInputManager(mWindow->getNativeWindow());
        mScriptsLibrary.open();
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
        mWindow = nullptr;
        mRegistry.clean();
        mHighRenderer.terminate();
        mScriptsLibrary.close();
    }

    int OrbitalApplication::run(int argc, char** argv)
    {
        Files::SetBinaryDir(argv[0]);
        initialize();
        Orbital::Logger::Log("Looping...");

        Time t0;
        Time dt;

        while (!mWindow->shouldClose())
        {
            dt = Time() - t0;
            RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderAPI::Clear();

            update(dt);
            t0 = Time();

            mWindow->swapBuffers();

            pollEvents();
        }

        terminate();

        Logger::Log("Exiting application normally");
        return 0;
    }
}
