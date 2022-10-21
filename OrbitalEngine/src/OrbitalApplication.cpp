#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalTools/Files.h"
#include "OrbitalEngine/Scene.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {
        LOGFUNC();
    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        Services::Renderer::Initialize(new HighRenderer);
        mWindow = &Services::Renderer::GetWindow(); // TODO make the window a service
        initializeInputManager(mWindow->getNativeWindow());
        Services::ScriptEngine::Initialize(new ScriptsLibraryLoader);

        Services::Scene::Initialize(new Orbital::Scene);
        // Registering built-in components
        Services::Scene::RegisterComponentType<TransformComponent>();
        Services::Scene::RegisterComponentType<MeshComponent>();
        Services::Scene::RegisterComponentType<NativeScriptManager>();
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
        mWindow = nullptr;
        Services::Scene::Terminate();
        Services::Renderer::Terminate();
        Services::ScriptEngine::Terminate();
    }

    int OrbitalApplication::run(int argc, char** argv)
    {
        Files::SetBinaryDir(argv[0]);
        initialize();
        Orbital::Logger::Log("Looping...");

        Time t0;
        Time dt;

        onLoad();
        Services::Scene::OnLoad();

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
        Services::Scene::OnUpdate(dt);
    }
}
