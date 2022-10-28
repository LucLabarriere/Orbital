#pragma once

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
		friend OrbitalApplication;
		SceneManager* mInstance = nullptr;
	};
} // namespace Orbital
