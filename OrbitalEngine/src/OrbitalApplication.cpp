#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalTools/Files.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
        : mServices()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {
        LOGFUNC();
    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");

        // Initializing Renderer
        auto highRenderer = std::make_shared<HighRenderer>();

        Logger::Trace("Initializing InputManager");
        mWindow = &highRenderer->getWindow();
        initializeInputManager(mWindow->getNativeWindow()); // Service ?

        Logger::Trace("Initializing Script Engine");
        auto scriptsLibraryLoader = std::make_shared<ScriptsLibraryLoader>();

        Logger::Trace("Initializing Scene Manager");
        auto sceneManager = std::make_shared<SceneManager>(SceneServiceManager::Create(
            highRenderer, scriptsLibraryLoader
        ));

        scriptsLibraryLoader->setServices(ServiceManager<ECSService, ScenesService>::Create(
            sceneManager->getCurrentScene(),
            sceneManager
        ));

        Logger::Trace("Storing Services");

        mServices = CompleteServiceManager::Create(
            sceneManager->getCurrentScene(),
            sceneManager,
            scriptsLibraryLoader,
            highRenderer
        );

        LOGVAR(mServices.ECS.mInstance == nullptr);

        Logger::Trace("Register component types");
        mServices.ECS.RegisterComponentType<TransformComponent>();
        mServices.ECS.RegisterComponentType<MeshComponent>();
        mServices.ECS.RegisterComponentType<NativeScriptManager>();
        Logger::Trace("Done Initializing OrbitalApplication");
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
        mWindow = nullptr;
        mServices.Scenes.Terminate();
        mServices.Renderer.Terminate();
        mServices.ScriptEngine.Terminate();
    }

    int OrbitalApplication::run(int argc, char** argv)
    {
        Files::SetBinaryDir(argv[0]);
        initialize();
        Orbital::Logger::Log("Looping...");

        Time t0;
        Time dt;

        onLoad();
        mServices.Scenes.OnLoad();

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

    void OrbitalApplication::update(const Time& dt)
    {
        mServices.Scenes.OnUpdate(dt);
    }
}
