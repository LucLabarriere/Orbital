#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	class Scene;
	enum class SceneState;

	using SceneManagerServices = Services<>;

	/**
	 * @class SceneManager
	 * @brief Handles scene loading, starting, cleaning up, etc...
	 */
	class OENGINE_API SceneManager : public SceneManagerServices
	{
	public:
		SceneManager(const SharedApplication& app);

		void terminate();

		void start();
		void pause();
		void resume();
		void stop();

		void preUpdate(const Time& dt);
		void update(const Time& dt);
		void postUpdate(const Time& dt);

		void setScene(Unique<Scene>&& scene);
		void setMainCamera(const Entity& camera);

		Unique<Scene>* getCurrentScene();
		SceneState getState() const;

	private:
		Unique<Scene> mScene;
		bool mRequestReload = false;
	};
} // namespace Orbital
