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
		SceneManager* sceneManager = nullptr;
		ScriptsLibraryLoader* libraryLoader = nullptr;
		Physics::Engine* physicsEngine = nullptr;
		HighRenderer* highRenderer = nullptr;
	};

	using AllServices = Services<AccessRenderer, AccessScenes, AccessECS, AccessScriptEngine>;

	class OENGINE_API OrbitalApplication : public InputManager, public std::enable_shared_from_this<OrbitalApplication>
	{
	public:
		virtual ~OrbitalApplication();

		virtual void initialize();
		virtual void terminate();

		inline SceneManager* getSceneManager() const
		{
			return mInstances.sceneManager;
		}
		inline ScriptsLibraryLoader* getLibraryLoader() const
		{
			return mInstances.libraryLoader;
		}
		inline Physics::Engine* getPhysicsEngine() const
		{
			return mInstances.physicsEngine;
		}
		inline HighRenderer* getHighRenderer() const
		{
			return mInstances.highRenderer;
		}

		int run(int argc, char** argv);

		virtual void onLoad(){};
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
