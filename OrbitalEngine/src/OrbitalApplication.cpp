#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Chrono.h"
#include "OrbitalTools/Files.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	OrbitalApplication::OrbitalApplication() : mInstances(), mServices()
	{
	}

	OrbitalApplication::~OrbitalApplication()
	{
		LOGFUNC();
	}

	void OrbitalApplication::initialize()
	{
		mInstances.settings = MakeRef<SettingsManager>();
		mInstances.highRenderer = MakeRef<HighRenderer>(shared_from_this());
		mInstances.libraryLoader = MakeRef<ScriptsLibraryLoader>(shared_from_this());
		mInstances.sceneManager = MakeRef<SceneManager>(shared_from_this());
		mInstances.physicsEngine = MakeRef<Physics::Engine>();

		mInstances.sceneManager->InitializeServices();

		mInstances.highRenderer->InitializeServices();
		mInstances.highRenderer->initialize(
			mInstances.settings->get<unsigned int>(Setting::WindowWidth),
			mInstances.settings->get<unsigned int>(Setting::WindowHeight)
		);

		mInstances.libraryLoader->InitializeServices();

		// mInstances.physicsEngine->InitializeServices();
		// mInstances.physicsEngine->initialize();

		mServices = AllServices(shared_from_this());
		mServices.InitializeServices();

		mWindow = &mInstances.highRenderer->getWindow();
		initializeInputManager((void*)mWindow->getNativeWindow()); // Service ?

		mInstances.libraryLoader->registerLibrary("OrbitalScripts");
		mInstances.libraryLoader->registerScript("OrbitalScripts", "FreeCameraController");

		mInstances.settings->setCallback(
			Setting::WindowWidth,
			[&]()
			{
				unsigned int w = mInstances.settings->get<unsigned int>(Setting::WindowWidth);
				unsigned int h = mInstances.settings->get<unsigned int>(Setting::WindowHeight);

				this->mWindow->resize(w, h);
			}
		);

		mInstances.settings->setCallback(
			Setting::WindowHeight,
			[&]()
			{
				unsigned int w = mInstances.settings->get<unsigned int>(Setting::WindowWidth);
				unsigned int h = mInstances.settings->get<unsigned int>(Setting::WindowHeight);

				this->mWindow->resize(w, h);
			}
		);

		mInstances.settings->setCallback(
			Setting::WindowMode, [&]() { this->mWindow->setWindowMode(mInstances.settings->get<Window::Mode>(Setting::WindowMode)); }
		);

		mInstances.settings->setCallback(
			Setting::VSync, [&]() { this->mWindow->setVSync(mInstances.settings->get<bool>(Setting::VSync)); }
		);
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

		// Deleting scripts requires the dll to be open. Thus, the loader must be terminated at the end
		mInstances.libraryLoader->terminate();
		mInstances.libraryLoader.reset();

		Logger::Log("Application terminated");
	}

	int OrbitalApplication::run(int argc, char** argv)
	{
		Files::SetBinaryDir(argv[0]);
		initialize();

		onLoad();
		mServices.Scenes.OnLoad();
		mRunning = true;

		Time dt;
		Chrono frametimeChrono;
		Chrono deltatimeChrono;

		onStart();
		mServices.Scenes.OnStart();

		Orbital::Logger::Log("Looping...");

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
			mInstances.settings->handleCallbacks();
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
