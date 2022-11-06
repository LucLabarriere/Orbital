#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Entity.h"
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
		void onUpdate(const Time& dt);

		Registry** getRegistry()
		{
			return &mRegistry;
		}

	protected:
		friend SceneManager;

		Registry* mRegistry;
	};
} // namespace Orbital
