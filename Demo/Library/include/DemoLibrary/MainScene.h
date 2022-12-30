#pragma once

#include "OrbitalEngine/Scene.h"
#include "DemoLibrary/Components.h"
#include "DemoScripts/CoreScript.h"
#include "OrbitalScripts/FreeCameraController.h"

using namespace Orbital;

namespace Demo
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
} // namespace Demo
