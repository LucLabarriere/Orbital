#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	using SceneManagerServices = Services<>;

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
		 * @brief Initializes the SceneManager
		 */
		void initialize();

		/**
		 * @brief Terminates the SceneManager
		 */
		void terminate();

		/**
		 * @brief Calles the onLoad() function of the current scene
		 */
		void onLoad();

		/**
		 * @brief Calles the onCleanUp() function of the current scene
		 */
		void onCleanUp();

		/**
		 * @brief Calles the onStart() function of the current scene
		 */
		void onStart();

		/**
		 * @brief Calles the onupdate() function of the current scene
		 *
		 * @param dt : Delta time
		 */
		void onUpdate(const Time& dt);

		/**
		 * @brief Get the current scene
		 *
		 * @return std::weak_ptr<Scene> : Ptr to the current scene
		 */
		std::weak_ptr<Scene> getCurrentScene()
		{
			return mScene;
		}

	private:
		std::shared_ptr<Scene> mScene = nullptr;
	};
} // namespace Orbital
