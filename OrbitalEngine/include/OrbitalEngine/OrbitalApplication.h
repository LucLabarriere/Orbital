#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services/ApplicationServices.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalInputs/Event.h"

namespace Orbital
{
	class Window;
	class SceneManager;
	class ScriptsLibraryLoader;
	class PhysicsEngine;
	class HighRenderer;

	struct InstanceContainer
	{
		SceneManager* sceneManager = nullptr;
		ScriptsLibraryLoader* libraryLoader = nullptr;
		PhysicsEngine* physicsEngine = nullptr;
		HighRenderer* highRenderer = nullptr;
	};

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
		inline PhysicsEngine* getPhysicsEngine() const
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

	protected:
		OrbitalApplication();

		Window* mWindow; // Make service ?
		InstanceContainer mInstances;
		AllServices mServices;
	};
} // namespace Orbital
