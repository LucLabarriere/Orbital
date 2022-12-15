#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalEngine/ECS/Components.h"

namespace Orbital
{
	EnemyScript::EnemyScript(const Entity& baseEntity)
		: NativeScript(baseEntity), mSpeed(0.3f)
	{
	}

	void EnemyScript::onLoad()
	{
	}

	void EnemyScript::onStart()
	{
	}

	void EnemyScript::onCreate()
	{
		get<MeshComponent>()->setColor({1.0f, 1.0f, 1.0f, 1.0f});
		mChrono.reset();
		mLifetime = 6.0f;
		mMaxHealth = 3;
		this->health = mMaxHealth;
	}

	void EnemyScript::onPreUpdate(const Time& dt)
	{
	}

	void EnemyScript::onUpdate(const Time& dt)
	{
		if (mChrono.measure().seconds() > mLifetime)
		{
			ECS.RequestDeleteEntity(mEntityID);
			return;
		}

		auto& playerTransform = *mPlayer.get<TransformComponent>();
		auto& transform = *get<TransformComponent>(); 

		auto direction = Maths::Normalize(playerTransform.position - transform.position);

		transform.position += direction * dt.seconds() * mSpeed;
	}
	
	void EnemyScript::getHit()
	{
		this->health -= 1;

		if (health <= 0)
		{
			ECS.RequestDeleteEntity(mEntityID);
			return;
		}

		float color = (float)this->health / (float)mMaxHealth;
		get<MeshComponent>()->setColor({ 1 - color, color, color, 1.0f});
	}

	OE_DEFINE_CREATOR(EnemyScript);

} // namespace Orbital
