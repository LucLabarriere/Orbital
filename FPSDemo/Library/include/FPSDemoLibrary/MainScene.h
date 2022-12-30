#pragma once

#include "OrbitalEngine/Scene.h"
#include "FPSDemoLibrary/Components.h"
#include "FPSDemoScripts/CoreScript.h"
#include "OrbitalScripts/FreeCameraController.h"

using namespace Orbital;

namespace FPSDemo
{
	class MainScene : public Scene
	{
	public:
		MainScene(const SharedApplication& app) : Scene(app)
		{
		}
		virtual ~MainScene() override {};
		
		virtual void initialize() override
		{
		}

		virtual void preLoad() override
		{
			mManager->registerComponentType<Health>();

			auto e = createEntity();
			e.push<CoreScript>();
			e.push<FreeCameraController>();
		}
	};
} // namespace FPSDemo
