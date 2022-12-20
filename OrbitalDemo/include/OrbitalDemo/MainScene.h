#pragma once

#include "OrbitalEngine/Scene.h"
#include "OrbitalScripts/CoreDemoApplication.h"
#include "OrbitalScripts/Components/Components.h"

using namespace Orbital;

class MainScene : public Scene
{
public:
	MainScene(const SharedApplication& app) : Scene(app)
	{
	}

	virtual void onLoad() override
	{
		mManager->registerComponentType<Health>();

		ScriptEngine.RegisterScript("CoreDemoApplication");
		ScriptEngine.RegisterScript("PlayerController");
		ScriptEngine.RegisterScript("SpawnEnemies");
		ScriptEngine.RegisterScript("EnemyScript");
		ScriptEngine.RegisterScript("WeaponPickup");
		ScriptEngine.RegisterScript("ProjectileScript");

		auto e = createEntity();
		e.push<CoreDemoApplication>();

		// Don't forget to call the parent onLoad function at the end
		Scene::onLoad();
	}
};
