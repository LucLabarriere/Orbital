#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services/ECSInterface.h"
// #include "OrbitalEngine/Services/PhysicsInterface.h"
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
		Ref<SceneManager> sceneManager = nullptr;
		Ref<ScriptsLibraryLoader> libraryLoader = nullptr;
		Ref<Physics::Engine> physicsEngine = nullptr;
		Ref<HighRenderer> highRenderer = nullptr;
	};

	// TODO Add the physics engine or remove if not needed
	using AllServices = Services<AccessRenderer, AccessScenes, AccessECS, AccessScriptEngine>;

	class OENGINE_API OrbitalApplication : public InputManager, public std::enable_shared_from_this<OrbitalApplication>
	{
	public:
		virtual ~OrbitalApplication();

		virtual void initialize();
		virtual void terminate();

		inline WeakRef<SceneManager> getSceneManager() const
		{
			return mInstances.sceneManager;
		}
		inline WeakRef<ScriptsLibraryLoader> getLibraryLoader() const
		{
			return mInstances.libraryLoader;
		}
		inline WeakRef<Physics::Engine> getPhysicsEngine() const
		{
			return mInstances.physicsEngine;
		}
		inline WeakRef<HighRenderer> getHighRenderer() const
		{
			return mInstances.highRenderer;
		}

		int run(int argc, char** argv);

		virtual void initializeComponents(){};
		virtual void onStart(){};
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
