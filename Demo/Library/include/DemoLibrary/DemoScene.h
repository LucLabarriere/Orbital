#pragma once
#include "DemoLibrary/Components.h"
#include "DemoScripts/CoreScript.h"
#include "OrbitalEngine/Scene.h"
#include "OrbitalScripts/Camera2DController.h"

using namespace Orbital;

namespace Demo
{
	class DemoScene : public Scene
	{
	public:
		DemoScene(const SharedApplication& app) : Scene(app){};
		virtual ~DemoScene() override{};

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
} // namespace Demo
