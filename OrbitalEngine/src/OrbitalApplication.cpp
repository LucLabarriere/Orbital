#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalScripts/CoreEditorApplication.h"
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

        // Registering built-in components
        mRegistry.registerComponentType<TransformComponent>();
        mRegistry.registerComponentType<MeshComponent>();
        mRegistry.registerComponentType<NativeScriptManager>();

        Service<Registry>::Initialize(mRegistry);
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

        auto e = Service<Registry>::Get().createEntity();
        e.push<NativeScriptManager>()->push("CoreEditorApplication", e);

        for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
        {
            manager.onLoad();
        }

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

    void OrbitalApplication::update(Time& dt)
    {
        if (mScriptsLibrary.lastCompilationSucceeded())
        {
            for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
            {
                manager.onUpdate(dt);
            }
        }

        for (auto& [ uuid, mc ] : mRegistry.components<MeshComponent>())
        {
            mHighRenderer.draw(mc);
        }
    }
}
