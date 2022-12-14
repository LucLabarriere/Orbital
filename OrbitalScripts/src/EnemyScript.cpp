#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalEngine/ECS/Components.h"

namespace Orbital
{
	EnemyScript::EnemyScript(const Entity& baseEntity)
		: NativeScript(baseEntity), mHealth(3), mSpeed(0.3f)
	{
	}

	void EnemyScript::onLoad()
	{
	}

	void EnemyScript::onStart()
	{
	}

	void EnemyScript::onPreUpdate(const Time& dt)
	{
	}

	void EnemyScript::onUpdate(const Time& dt)
	{
		auto& playerTransform = *mPlayer.get<TransformComponent>();
		auto& transform = *get<TransformComponent>(); 

		auto direction = Maths::Normalize(playerTransform.position - transform.position);

		transform.position += direction * dt.seconds() * mSpeed;
	}

	OE_DEFINE_CREATOR(EnemyScript);

} // namespace Orbital
