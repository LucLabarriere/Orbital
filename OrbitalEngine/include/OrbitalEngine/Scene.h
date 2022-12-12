#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"

namespace Orbital
{
	class SceneManager;

	using SceneServices = Services<AccessScriptEngine>;

	class OENGINE_API Scene : protected SceneServices
	{
	public:
		/**
		 * @brief Initializs the Scene with the appropriate services
		 *
		 * @param services
		 */
		Scene(const SharedApplication& app);

		void terminate();
		void reset();

		Entity createEntity();

		void onLoad();
		void onCleanUp();
		void onStart();
		void onPreUpdate(const Time& dt);
		void onUpdate(const Time& dt);

		std::weak_ptr<ECSManager> getManager()
		{
			return mManager;
		}

	protected:
		friend SceneManager;

		std::shared_ptr<ECSManager> mManager;
	};
} // namespace Orbital
