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
		 * @brief Initializes the Scene with the appropriate services
		 *
		 * @param app
		 */
		Scene(const SharedApplication& app);

		void terminate();
		void initialize();
		void reset();

		Entity createEntity();
		void deleteEntity(const EntityID& id);
		void requestDeleteEntity(const EntityID& id);

		virtual void onLoad();
		virtual void onCleanUp();
		virtual void onStart();
		virtual void onPreUpdate(const Time& dt);
		virtual void onUpdate(const Time& dt);
		virtual void postUpdate();

		Ref<ECSManager>* getManager()
		{
			return &mManager;
		}

	protected:
		friend SceneManager;

		Ref<ECSManager> mManager;
	};
} // namespace Orbital
