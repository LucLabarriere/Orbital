#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	class ProjectileScript: public NativeScript
	{
	public:
		ProjectileScript(const Entity& e);
		virtual ~ProjectileScript(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onCreate() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(ProjectileScript);

		Maths::Vec3 direction;

		float speed = 1.0f;
		float damage = 1.0f;
		float lifetime = 2.0f;

	private:
		Chrono mChrono;
	};

	OE_DECLARE_CREATOR(ProjectileScript);
} // namespace Orbital
