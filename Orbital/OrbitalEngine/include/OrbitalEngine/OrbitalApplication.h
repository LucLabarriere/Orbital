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

#include "OrbitalEngine/DebugLayer.h"
#include "OrbitalEngine/Scene.h"
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
		OrbitalApplication() = default;
		virtual ~OrbitalApplication() = default;

		auto run(int argc, char** argv) -> int;

		template <typename T, typename = std::enable_if<std::is_base_of<Scene, T>::value>>
		auto changeScene() -> void
		{
			auto scene = MakeUnique<T>(shared_from_this());
			mInstances.sceneManager->setScene(std::move(scene));
		}

		auto getSceneManager() const -> WeakRef<SceneManager>;
		auto getLibraryLoader() const -> WeakRef<ScriptsLibraryLoader>;
		auto getPhysicsEngine() const -> WeakRef<Physics::Engine>;
		auto getHighRenderer() const -> WeakRef<HighRenderer>;
		auto getSettings() const -> WeakRef<SettingManager>;
		auto getStatistics() const -> WeakRef<StatisticManager>;

	protected:
		virtual auto onInitialize() -> void = 0;

		auto onEvent(Event& e) -> void override;
		auto onKeyPressed(KeyPressedEvent& e) -> bool override;

		auto requestExit() -> void;
		auto initialize() -> void;
		auto terminate() -> void;
		auto preUpdate(const Time& dt) -> void;
		auto update(const Time& dt) -> void;
		auto postUpdate(const Time& dt) -> void;

	protected:
		AllServices mServices;

	private:
		void initializeSettingsCallbacks();

		bool mRunning = false;
		Window* mWindow; // Make service ?
		InstanceContainer mInstances;
		Unique<DebugLayer> mDebugLayer = nullptr;
	};
} // namespace Orbital
