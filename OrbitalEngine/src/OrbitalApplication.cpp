#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Files.h"


namespace Orbital
{
	OrbitalApplication::OrbitalApplication() : mInstances(), mServices()
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
		mInstances.highRenderer = std::make_shared<HighRenderer>(shared_from_this());
		mInstances.libraryLoader = std::make_shared<ScriptsLibraryLoader>(shared_from_this());
		mInstances.sceneManager = std::make_shared<SceneManager>(shared_from_this());
		mInstances.physicsEngine = std::make_shared<Physics::Engine>();

		mInstances.sceneManager->InitializeServices();
		mInstances.sceneManager->initialize();

		mInstances.highRenderer->InitializeServices();
		mInstances.highRenderer->initialize();

		mInstances.libraryLoader->InitializeServices();
		mInstances.libraryLoader->initialize();

		//mInstances.physicsEngine->InitializeServices();
		//mInstances.physicsEngine->initialize();

		Logger::Debug("Initializing Application services");
		mServices = AllServices(shared_from_this());
		mServices.InitializeServices();

		mWindow = &mInstances.highRenderer->getWindow();
		initializeInputManager((void*)mWindow->getNativeWindow()); // Service ?

		mServices.ECS.RegisterComponentType<TransformComponent>();
		mServices.ECS.RegisterComponentType<PhysicsComponent>();
		mServices.ECS.RegisterComponentType<MeshComponent>();
		mServices.ECS.RegisterComponentType<MeshFilter>();
		mServices.ECS.RegisterComponentType<NativeScriptManager>();
	}

	void OrbitalApplication::terminate()
	{
		Logger::Log("Terminating application");
		mWindow = nullptr;
		mInstances.highRenderer->terminate();
		mInstances.sceneManager->terminate();

		mInstances.highRenderer.reset();
		mInstances.physicsEngine.reset();
		mInstances.sceneManager.reset();

		// Deleting scripts require the dll to be open. Thus, the loader must be terminated at the end
		mInstances.libraryLoader->terminate();
		mInstances.libraryLoader.reset();

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
		mRunning = true;

		while (!mWindow->shouldClose() && mRunning)
		{
			dt = Time() - t0;
			pollEvents();

			RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			RenderAPI::Clear();

			preUpdate(dt);
			update(dt);
			t0 = Time();

			mWindow->swapBuffers();
		}

		terminate();

		Logger::Log("Exiting application normally");
		return 0;
	}

	void OrbitalApplication::preUpdate(const Time& dt)
	{
		mInstances.sceneManager->onPreUpdate(dt);
	}

	void OrbitalApplication::update(const Time& dt)
	{
		//mInstances.physicsEngine->onUpdate2D(dt);
		//mInstances.physicsEngine->onUpdate3D(dt);

		//mInstances.physicsEngine->verletIntegration<RigidBody2D>(dt, mServices.ECS.Components<RigidBody2D>());
		//mInstances.physicsEngine->verletIntegration<RigidBody3D>(dt, mServices.ECS.Components<RigidBody3D>());

		mInstances.physicsEngine->onUpdate(dt.seconds());
		mInstances.sceneManager->onUpdate(dt);
		mServices.Renderer.OnUpdate();
	}

	void OrbitalApplication::requestExit()
	{
		mRunning = false;
	}
} // namespace Orbital
