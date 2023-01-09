#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services/ECSInterface.h"
// #include "OrbitalEngine/Services/PhysicsInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"
#include "OrbitalEngine/Services/SettingsInterface.h"
#include "OrbitalEngine/Services/StatisticsInterface.h"

#include "OrbitalEngine/SceneManager.h"

#include "OrbitalImGui/DebugLayer.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	class Window;
	class SceneManager;
	class ScriptsLibraryLoader;
	class HighRenderer;
	class SettingManager;
	class StatisticManager;

	struct InstanceContainer
	{
		Ref<SettingManager> settings = nullptr;
		Ref<StatisticManager> statistics = nullptr;
		Ref<SceneManager> sceneManager = nullptr;
		Ref<ScriptsLibraryLoader> libraryLoader = nullptr;
		Ref<Physics::Engine> physicsEngine = nullptr;
		Ref<HighRenderer> highRenderer = nullptr;
	};

	// TODO Add the physics engine or remove if not needed
	using AllServices =
		Services<AccessRenderer, AccessScenes, AccessECS, AccessScriptEngine, AccessSettings, AccessStatistics>;

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
		inline WeakRef<SettingManager> getSettings() const
		{
			return mInstances.settings;
		}
		inline WeakRef<StatisticManager> getStatistics() const
		{
			return mInstances.statistics;
		}

		int run(int argc, char** argv);

		template <typename T, typename = std::enable_if<std::is_base_of<Scene, T>::value>>
		void loadScene()
		{
			mInstances.sceneManager->initialize<T>();
		}

		virtual void onStart(){};
		virtual void onLoad(){};
		virtual void preUpdate(const Time& dt);
		virtual void update(const Time& dt);
		virtual void postUpdate(const Time& dt);
		virtual bool onKeyPressed(KeyPressedEvent& e) override;

		void requestExit();

	protected:
		OrbitalApplication();

		bool mRunning = false;
		Window* mWindow; // Make service ?
		InstanceContainer mInstances;
		AllServices mServices;
		Unique<Gui::DebugLayer> mDebugLayer = nullptr;
	};
} // namespace Orbital
