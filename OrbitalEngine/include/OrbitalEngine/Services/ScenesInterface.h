#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class SceneManager;

	class OENGINE_API ScenesInterface : public ServiceInterface
	{
	public:
		ScenesInterface(const SharedApplication& app);
		void Initialize();

		void OnLoad();
		void OnCleanUp();
		void OnStart();
		void OnUpdate(const Time& dt);

	private:
		SceneManager* mInstance = nullptr;
	};

	OCREATE_SERVICE(Scenes);

} // namespace Orbital
