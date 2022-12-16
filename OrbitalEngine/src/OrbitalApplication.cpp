#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Files.h"
#include "OrbitalTools/Chrono.h"


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
		mInstances.highRenderer = MakeRef<HighRenderer>(shared_from_this());
		mInstances.libraryLoader = MakeRef<ScriptsLibraryLoader>(shared_from_this());
		mInstances.sceneManager = MakeRef<SceneManager>(shared_from_this());
		mInstances.physicsEngine = MakeRef<Physics::Engine>();

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

		onLoad();
		mServices.Scenes.OnLoad();
		mRunning = true;

		Time dt;
		Chrono frametimeChrono;
		Chrono deltatimeChrono;

		onStart();
		mServices.Scenes.OnStart();

		while (!mWindow->shouldClose() && mRunning)
		{
			pollEvents();

			RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			RenderAPI::Clear();

			dt = deltatimeChrono.measure();
			deltatimeChrono.reset();
			preUpdate(dt);
			update(dt);

			if (frametimeChrono.measure().seconds() > 0.5f)
			{
				Logger::Log("Frame time : ", dt.milliSeconds(), " ms");
				frametimeChrono.reset();
			}

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
		mInstances.physicsEngine->onUpdate(dt.seconds());
		mInstances.sceneManager->onUpdate(dt);
		mServices.Renderer.OnUpdate();
		mInstances.sceneManager->postUpdate();
	}

	void OrbitalApplication::requestExit()
	{
		mRunning = false;
	}
} // namespace Orbital
