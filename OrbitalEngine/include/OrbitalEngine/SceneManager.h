#pragma once

#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Services/ApplicationServices.h"

namespace Orbital
{
	using SceneManagerServices = Services<>;

	class OENGINE_API SceneManager : public SceneManagerServices
	{
	public:
		/**
		 * @brief Initializes the scene with appropriate services
		 *
		 * @param services
		 */
		SceneManager(const SharedApplication& app);

		void initialize();
		void terminate();

		void onLoad();
		void onCleanUp();
		void onStart();
		void onUpdate(const Time& dt);

		Scene** getCurrentScene()
		{
			return &mScene;
		}

	private:
		Scene* mScene = nullptr;
	};
} // namespace Orbital
