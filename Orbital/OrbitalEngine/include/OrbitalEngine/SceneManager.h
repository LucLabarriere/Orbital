#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	enum class SceneState
	{
		Running = 0,
		Paused,
		Stoped
	};

	using SceneManagerServices = Services<AccessRenderer>;

	/**
	 * @class SceneManager
	 * @brief Handles scene loading, starting, cleaning up, etc...
	 *
	 */
	class OENGINE_API SceneManager : public SceneManagerServices
	{
	public:
		SceneManager(const SharedApplication& app);

		/**
		 * @brief Initializes the Scene
		 *
		 * Pass in "Scene" as template type to initialize the default empty scene.
		 * You can also pass in your custom scene type.
		 *
		 * @tparam T Type of the Scene
		 */
		template <typename T, typename = std::enable_if<std::is_base_of<Scene, T>::value>>
		void initialize()
		{
			mScene = MakeUnique<T>(mApp);
			mScene->initialize();
		}

		/**
		 * @brief Terminates the SceneManager
		 */
		void terminate();

		/**
		 * @brief Calls the onLoad() function of the current scene
		 */
		void onLoad();

		/**
		 * @brief Calls the onCleanUp() function of the current scene
		 */
		void onCleanUp();

		/**
		 * @brief Calls the onStart() function of the current scene
		 */
		void onStart();

		/**
		 * @brief Calls the onPreUpdate() function of the current scene
		 *
		 * @param dt : Delta time
		 */
		void onPreUpdate(const Time& dt);

		/**
		 * @brief Calls the onUpdate() function of the current scene
		 *
		 * @param dt : Delta time
		 */
		void onUpdate(const Time& dt);

		/**
		 * @brief calls post update functions
		 */
		void postUpdate();

		/**
		 * @brief Pauses the current scene
		 */
		void pause();

		/**
		 * @brief Resumes the current scene
		 */
		void resume();

		/**
		 * @brief Reloads the current scene
		 */
		void reload();

		/**
		 * @brief Get the current scene
		 *
		 * @return ptr to the current scene
		 */
		Unique<Scene>* getCurrentScene()
		{
			return &mScene;
		}

		inline SceneState getState() const
		{
			return mState;
		}

		void setMainCamera(const Entity& camera)
		{
			mScene->setMainCamera(camera);
		}

	private:
		Unique<Scene> mScene = nullptr;
		SceneState mState = SceneState::Stoped;
		bool mRequestReload = false;
	};
} // namespace Orbital
