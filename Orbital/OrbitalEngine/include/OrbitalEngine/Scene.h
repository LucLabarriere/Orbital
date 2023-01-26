#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"

namespace Orbital
{
	enum class SceneState
	{
		Uninitialized = 0,
		Running,
		Paused,
		Stoped
	};

	enum class Layer // TODO Move to a Layer.h file
	{
		Dev,
		Main,
		Gui,
		SIZE
	};

	class SceneManager;

	using SceneServices = Services<AccessScriptEngine, AccessRenderer>;

	class ORBITAL_ENGINE_API Scene : protected SceneServices
	{
	public:
		/**
		 * @brief Initializes the Scene with the appropriate services
		 *
		 * @param app
		 */
		Scene(const SharedApplication& app);
		virtual ~Scene(){};

		void terminate();
		void initialize();

		virtual void preLoad() = 0;
		void load();
		void start();
		void pause();
		void resume();
		void stop();

		void preUpdate(const Time& dt);
		void update(const Time& dt);
		void postUpdate(const Time& dt);

		auto createEntity() -> Entity;
		void deleteEntity(const EntityID& id);
		void requestDeleteEntity(const EntityID& id);

		[[nodiscard]] auto getManager() -> Ref<ECSManager>* { return &mManager; }
		[[nodiscard]] auto getState() const -> SceneState { return mState; }
		[[nodiscard]] auto getDevCamera() const -> Entity { return mDevCamera; }
		[[nodiscard]] auto getMainCamera() const -> Entity { return mMainCamera; }
		[[nodiscard]] auto getActiveCamera() const -> Entity
		{
			return (mState == SceneState::Running ? mMainCamera : mDevCamera);
		}

		void setMainCamera(const Entity& camera) { mMainCamera = camera; }

	protected:
		virtual void registerCustomComponents() = 0;

	private:
		void registerDefaultComponents(Ref<ECSManager>& manager);
		void render(Ref<ECSManager>& manager);

	protected:
		friend SceneManager;

		Entity mMainCamera;
		Ref<ECSManager> mManager;
		SceneState mState = SceneState::Uninitialized;

	private:
		Ref<ECSManager> mDevManager;
		Entity mDevCamera;
	};
} // namespace Orbital
