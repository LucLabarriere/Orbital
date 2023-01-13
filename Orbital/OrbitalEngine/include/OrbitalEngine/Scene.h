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
		virtual ~Scene(){};

		void terminate();
		virtual void initialize() = 0;
		void reset();

		Entity createEntity();
		void deleteEntity(const EntityID& id);
		void requestDeleteEntity(const EntityID& id);

		virtual void preLoad() = 0;
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

		inline Entity getDevCamera() const
		{
			return mDevCamera;
		}

		void setMainCamera(const Entity& camera)
		{
			mMainCamera = camera;
		}

		inline Entity getMainCamera() const
		{
			return mMainCamera;
		}


	protected:
		friend SceneManager;

		Entity mDevCamera;
		Entity mMainCamera;
		Ref<ECSManager> mManager;
		Ref<ECSManager> mDevManager;
	};
} // namespace Orbital
