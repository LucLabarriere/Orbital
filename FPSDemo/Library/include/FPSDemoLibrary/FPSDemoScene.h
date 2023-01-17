#pragma once

#include "FPSDemoLibrary/Components.h"
#include "FPSDemoScripts/CoreScript.h"
#include "OrbitalEngine/Scene.h"
#include "OrbitalScripts/FreeCameraController.h"

using namespace Orbital;

namespace FPSDemo
{
	class FPSDemoScene : public Scene
	{
	public:
		FPSDemoScene(const SharedApplication& app) : Scene(app){};
		virtual ~FPSDemoScene() override{};

		virtual void registerCustomComponents() override
		{
			mManager->registerComponentType<Health>();
		}

		virtual void preLoad() override
		{
			auto e = createEntity();
			e.push<CoreScript>();
		}
	};
} // namespace FPSDemo
