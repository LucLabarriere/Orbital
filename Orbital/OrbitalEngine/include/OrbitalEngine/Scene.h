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

		auto getManager() -> Ref<ECSManager>* { return &mManager; }

		inline auto getDevCamera() const -> Entity { return mDevCamera; }

		inline auto getMainCamera() const -> Entity { return mMainCamera; }

		inline auto getActiveCamera() const -> Entity
		{
			return (mState == SceneState::Running ? mMainCamera : mDevCamera);
		}

		inline void setMainCamera(const Entity& camera) { mMainCamera = camera; }

		inline auto getState() const -> SceneState { return mState; }

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
