#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalScripts/Components/Components.h"

EnemyScript::EnemyScript(const Entity& baseEntity) : NativeScript(baseEntity), mSpeed(0.3f)
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
	auto filter = push<MeshFilter>(MeshType::Sphere);
	auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
	auto mesh = push<MeshComponent>();
	auto& health = *push<Health>();

	health.max = 3.0f;
	health.current = health.max;

	mesh->setColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	mChrono.reset();
	mLifetime = 6.0f;
	mMaxScale = 0.2f;

	get<TransformComponent>()->scale *= mMaxScale;
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

	auto& health = *get<Health>();

	float color = health.current / health.max;
	get<MeshComponent>()->setColor({ 1 - color, 0.0f, color, 1.0f });

	transform.scale = Maths::Vec3(1.0f) * health.current / health.max * mMaxScale + 0.2f;
}

OE_DEFINE_CREATOR(EnemyScript);
