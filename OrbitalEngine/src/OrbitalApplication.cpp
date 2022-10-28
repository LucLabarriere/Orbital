#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Files.h"

#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Physics/PhysicsEngine.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
	OrbitalApplication::OrbitalApplication() : mInstances(), mServices(nullptr)
	{
		Logger::Debug("Entry points");
	}

	OrbitalApplication::~OrbitalApplication()
	{
		LOGFUNC();
	}

	void OrbitalApplication::initialize()
	{
		Logger::Log("Creating instances");
		mInstances.highRenderer = new HighRenderer(shared_from_this());
		mInstances.libraryLoader = new ScriptsLibraryLoader(shared_from_this());
		mInstances.sceneManager = new SceneManager(shared_from_this());
		mInstances.physicsEngine = new PhysicsEngine(shared_from_this());

		mInstances.sceneManager->InitializeServices();
		mInstances.sceneManager->initialize();

		mInstances.highRenderer->InitializeServices();
		mInstances.highRenderer->initialize();

		mInstances.libraryLoader->InitializeServices();
		mInstances.libraryLoader->initialize();

		mInstances.physicsEngine->InitializeServices();
		mInstances.physicsEngine->initialize();

		Logger::Debug("Initializing Application services");
		mServices = AllServices(shared_from_this());
		mServices.InitializeServices();

		mWindow = &mInstances.highRenderer->getWindow();
		initializeInputManager((void*)mWindow->getNativeWindow()); // Service ?

		Logger::Trace("Register component types");
		mServices.ECS.RegisterComponentType<TransformComponent>();
		mServices.ECS.RegisterComponentType<MeshComponent>();
		mServices.ECS.RegisterComponentType<NativeScriptManager>();
		mServices.ECS.RegisterComponentType<DynamicsComponent>();
		mServices.ECS.RegisterComponentType<Collider>();
		Logger::Trace("Done Initializing OrbitalApplication");
	}

	void OrbitalApplication::terminate()
	{
		Logger::Log("Terminating application");
		mWindow = nullptr;
		mInstances.physicsEngine->terminate();
		mInstances.highRenderer->terminate();
		mInstances.sceneManager->terminate();

		delete mInstances.highRenderer;
		delete mInstances.physicsEngine;
		delete mInstances.sceneManager;

		// Deleting scripts require the dll to be open. Thus, the loader must be terminated at the end
		mInstances.libraryLoader->terminate();
		delete mInstances.libraryLoader;
		Logger::Log("Application terminated");
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
			pollEvents();

			RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			RenderAPI::Clear();

			update(dt);
			t0 = Time();

			mWindow->swapBuffers();
		}

		terminate();

		Logger::Log("Exiting application normally");
		return 0;
	}

	void OrbitalApplication::update(const Time& dt)
	{
		mServices.Physics.OnUpdate(dt);
		mServices.Scenes.OnUpdate(dt);
		mServices.Renderer.OnUpdate();
	}
} // namespace Orbital
