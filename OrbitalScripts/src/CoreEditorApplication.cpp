#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalScripts/SpawnEnemies.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void CoreEditorApplication::onLoad()
	{
		auto player = ECS.CreateEntity();
		player.push<PlayerController>();

		auto spawner = push<SpawnEnemies>();
		spawner->setPlayer(player.getEntityID());
	}

	void CoreEditorApplication::onStart()
	{
	}

	void CoreEditorApplication::onPreUpdate(const Time& dt)
	{
	}

	OE_DEFINE_CREATOR(CoreEditorApplication);

} // namespace Orbital
