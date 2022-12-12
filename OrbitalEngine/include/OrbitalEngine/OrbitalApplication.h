#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services/ECSInterface.h"
//#include "OrbitalEngine/Services/PhysicsInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"

#include "OrbitalInputs/Core.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	class Window;
	class SceneManager;
	class ScriptsLibraryLoader;
	class HighRenderer;

	struct InstanceContainer
	{
		std::shared_ptr<SceneManager> sceneManager = nullptr;
		std::shared_ptr<ScriptsLibraryLoader> libraryLoader = nullptr;
		std::shared_ptr<Physics::Engine> physicsEngine = nullptr;
		std::shared_ptr<HighRenderer> highRenderer = nullptr;
	};

	using AllServices = Services<AccessRenderer, AccessScenes, AccessECS, AccessScriptEngine>;

	class OENGINE_API OrbitalApplication : public InputManager, public std::enable_shared_from_this<OrbitalApplication>
	{
	public:
		virtual ~OrbitalApplication();

		virtual void initialize();
		virtual void terminate();

		inline std::weak_ptr<SceneManager> getSceneManager() const
		{
			return mInstances.sceneManager;
		}
		inline std::weak_ptr<ScriptsLibraryLoader> getLibraryLoader() const
		{
			return mInstances.libraryLoader;
		}
		inline std::weak_ptr<Physics::Engine> getPhysicsEngine() const
		{
			return mInstances.physicsEngine;
		}
		inline std::weak_ptr<HighRenderer> getHighRenderer() const
		{
			return mInstances.highRenderer;
		}

		int run(int argc, char** argv);

		virtual void onLoad(){};
		virtual void preUpdate(const Time& dt);
		virtual void update(const Time& dt);
		void requestExit();

	protected:
		OrbitalApplication();

		bool mRunning = false;
		Window* mWindow; // Make service ?
		InstanceContainer mInstances;
		AllServices mServices;
	};
} // namespace Orbital
