#include "OrbitalScripts/CoreDemoApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalScripts/SpawnEnemies.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreDemoApplication::CoreDemoApplication(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void CoreDemoApplication::onLoad()
	{
		auto player = ECS.CreateEntity();
		player.push<PlayerController>();

		auto spawner = push<SpawnEnemies>();
		spawner->setPlayer(player.getEntityID());
	}

	void CoreDemoApplication::onStart()
	{
	}

	void CoreDemoApplication::onPreUpdate(const Time& dt)
	{
	}

	OE_DEFINE_CREATOR(CoreDemoApplication);

} // namespace Orbital
