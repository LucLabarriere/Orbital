#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/Settings.h"
#include "OrbitalEngine/Statistics.h"
#include "OrbitalScripts/FreeCameraController.h"

#include "OrbitalEngine/Scene.h"
#include "OrbitalImGui/Core.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
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
		mInstances.settings = MakeRef<SettingManager>();
		mInstances.statistics = MakeRef<StatisticManager>();
		mInstances.highRenderer = MakeRef<HighRenderer>(shared_from_this());
		mInstances.libraryLoader = MakeRef<ScriptsLibraryLoader>(shared_from_this());
		mInstances.sceneManager = MakeRef<SceneManager>(shared_from_this());
		mInstances.physicsEngine = MakeRef<Physics::Engine>();

		// SceneManager
		mInstances.sceneManager->InitializeServices();

		// HighRenderer
		mInstances.highRenderer->InitializeServices();
		mInstances.highRenderer->initialize(
			mInstances.settings->get<unsigned int>(Setting::WindowWidth),
			mInstances.settings->get<unsigned int>(Setting::WindowHeight)
		);

		// LibraryLoader
		mInstances.libraryLoader->InitializeServices();

		// PhysicsEngine
		// mInstances.physicsEngine->InitializeServices();
		// mInstances.physicsEngine->initialize();

		// Application services
		mServices = AllServices(shared_from_this());
		mServices.InitializeServices();

		// Initializing the window
		mWindow = &mInstances.highRenderer->getWindow();
		initializeInputManager((void*)mWindow->getNativeWindow()); // Service ?

		// Initializing core scripts
		mInstances.libraryLoader->registerLibrary("Orbital-Scripts");
		mInstances.libraryLoader->registerScript("Orbital-Scripts", "FreeCameraController");
		mInstances.libraryLoader->registerScript("Orbital-Scripts", "FPSCameraController");
		mInstances.libraryLoader->registerScript("Orbital-Scripts", "Camera2DController");

		// Initialize settings
		initializeSettingsCallbacks();

		// Initialize DebugLayer (TODO : switch to a Layer in the SceneManager ? or in the Scene)
		mDebugLayer = MakeUnique<DebugLayer>(shared_from_this());
		mDebugLayer->initialize(mWindow);

		onInitialize();
		mInstances.sceneManager->start();
		mRunning = true;
	}

	void OrbitalApplication::terminate()
	{
		mWindow = nullptr;
		mDebugLayer->terminate();
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

	void OrbitalApplication::onEvent(Event& e)
	{
		if (Gui::CapturingKeyboardEvents())
		{
			Inputs::RegisterKeyboardEvents(false);
		}
		else
		{
			Inputs::RegisterKeyboardEvents(true);

			if (dispatchEvent<KeyPressedEvent>(e))
				return;
			if (dispatchEvent<KeyReleasedEvent>(e))
				return;
		}

		if (Gui::CapturingMouseEvents())
		{
			Inputs::RegisterMouseEvents(false);
		}
		else
		{
			Inputs::RegisterMouseEvents(true);

			if (dispatchEvent<MouseMoveEvent>(e))
				return;
			if (dispatchEvent<MouseButtonPressedEvent>(e))
				return;
			if (dispatchEvent<MouseButtonReleasedEvent>(e))
				return;
			if (dispatchEvent<MouseScrolledEvent>(e))
				return;
		}
	}

	int OrbitalApplication::run(int argc, char** argv)
	{
		Files::SetBinaryDir(argv[0]);

		initialize();
		Time dt;
		Chrono deltatimeChrono;

		while (!mWindow->shouldClose() && mRunning)
		{
			pollEvents();

			dt = deltatimeChrono.measure();
			deltatimeChrono.reset();

			preUpdate(dt);
			update(dt);
			postUpdate(dt);
		}

		terminate();

		return 0;
	}

	void OrbitalApplication::preUpdate(const Time& dt)
	{
		RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		RenderAPI::Clear();

		mDebugLayer->beginFrame();

		Inputs::UpdateDrag();
		mInstances.sceneManager->preUpdate(dt);
	}

	void OrbitalApplication::update(const Time& dt)
	{
		mInstances.physicsEngine->update(dt.seconds());
		mInstances.sceneManager->update(dt);
	}

	void OrbitalApplication::postUpdate(const Time& dt)
	{
		Unique<Scene>* scene = mInstances.sceneManager->getCurrentScene();
		CameraHandle camera = (*scene)->getActiveCamera().get<CameraComponent>();
		if (!camera.isValid())
		{
			Logger::Error("The camera was not set in the Core script of the game. Using the Dev camera instead");
			camera = (*scene)->getDevCamera().get<CameraComponent>();
		}
		mInstances.highRenderer->setCamera(camera);
		mInstances.highRenderer->onUpdate();
		mInstances.sceneManager->postUpdate(dt);
		mDebugLayer->endFrame();

		mInstances.statistics->get<float>(Statistic::FPS) = 1.0f / dt.seconds();
		mInstances.statistics->get<float>(Statistic::Frametime) = dt.milliSeconds();

		mWindow->swapBuffers();
		mInstances.settings->handleCallbacks();
		std::cout << std::flush;
	}

	bool OrbitalApplication::onKeyPressed(KeyPressedEvent& e)
	{
		if (e.getKey() == OE_KEY_F2)
		{
			Logger::Log("Recompiling scripts");
			mInstances.sceneManager->terminate();

			bool compilationSucceeded = mServices.ScriptEngine.Recompile();
			// bool compilationSucceeded = true;

			if (compilationSucceeded)
			{
				onInitialize(); // make a script specific function
			}
		}

		if (e.getKey() == OE_KEY_ESCAPE or (Inputs::IsKeyDown(OE_KEY_LEFT_ALT) and e.getKey() == OE_KEY_F4))
		{
			requestExit();
			return true;
		}

		else if (e.getKey() == OE_KEY_F3)
		{
			auto& windowMode = mServices.Settings.GetMut<Window::Mode>(Setting::WindowMode);

			switch (windowMode)
			{
			case Window::Mode::FullScreen:
			{
				windowMode = Window::Mode::Windowed;
				break;
			}
			case Window::Mode::Windowed:
			{
				windowMode = Window::Mode::FullScreen;
				break;
			}
			case Window::Mode::Borderless:
			{
				windowMode = Window::Mode::Windowed;
				break;
			}
			}
			return true;
		}

		else if (e.getKey() == OE_KEY_F4)
		{
			auto& mouseVisible = mServices.Settings.GetMut<bool>(Setting::MouseVisible);
			mouseVisible = !mouseVisible;

			return true;
		}

		else if (e.getKey() == OE_KEY_SPACE)
		{
			if (mInstances.sceneManager->getState() == SceneState::Running)
			{
				mInstances.sceneManager->pause();
			}
			else
			{
				mInstances.sceneManager->resume();
			}
		}

		return false;
	}

	void OrbitalApplication::requestExit()
	{
		mRunning = false;
	}

	void OrbitalApplication::initializeSettingsCallbacks()
	{
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
			Setting::WindowMode,
			[&]() { this->mWindow->setWindowMode(mInstances.settings->get<Window::Mode>(Setting::WindowMode)); }
		);

		mInstances.settings->setCallback(
			Setting::VSync, [&]() { this->mWindow->setVSync(mInstances.settings->get<bool>(Setting::VSync)); }
		);

		mInstances.settings->setCallback(
			Setting::WindowTitle,
			[&]() { this->mWindow->setTitle(mInstances.settings->get<std::string>(Setting::WindowTitle)); }
		);

		mInstances.settings->setCallback(
			Setting::MouseVisible,
			[&]() { this->mWindow->setMouseEnabled(mInstances.settings->get<bool>(Setting::MouseVisible)); }
		);
	}
} // namespace Orbital
