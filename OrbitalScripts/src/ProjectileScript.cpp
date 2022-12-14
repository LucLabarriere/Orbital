#include "OrbitalScripts/ProjectileScript.h"
#include "OrbitalEngine/ECS/Components.h"

namespace Orbital
{
	ProjectileScript::ProjectileScript(const Entity& baseEntity)
		: NativeScript(baseEntity)
	{
	}

	void ProjectileScript::onLoad()
	{
	}

	void ProjectileScript::onStart()
	{
	}

	void ProjectileScript::onCreate()
	{
		this->speed = 1.0f;
		this->lifetime = 0.6f;
		get<TransformComponent>()->scale *= 0.02f;
		mChrono.reset();
	}

	void ProjectileScript::onPreUpdate(const Time& dt)
	{
	}

	void ProjectileScript::onUpdate(const Time& dt)
	{
		if (mChrono.measure().seconds() > lifetime)
		{
			ECS.RequestDeleteEntity(mEntityID);
			return;
		}

		get<TransformComponent>()->position += this->direction * this->speed * dt.seconds();
	}

	OE_DEFINE_CREATOR(ProjectileScript);

} // namespace Orbital
