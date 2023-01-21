#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class SceneManager;
	enum class SceneState;

	class ORBITAL_ENGINE_API ScenesInterface : public ServiceInterface
	{
	public:
		ScenesInterface();
		ScenesInterface(const SharedApplication& app);
		void InitializeInterface();
		WeakRef<SceneManager> Get() const { return mInstance; }
		Unique<Scene>* GetCurrentScene();

		void OnLoad();
		void OnCleanUp();
		void OnStart();
		void OnUpdate(const Time& dt);

		void Pause();
		void Resume();
		void Reload();

		SceneState GetState();
		void SetMainCamera(const Entity& camera);

	private:
		WeakRef<SceneManager> mInstance;
	};

	OCREATE_SERVICE(Scenes);

} // namespace Orbital
