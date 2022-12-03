#pragma once

#include "OrbitalEngine/Components.h"
#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class OSCRIPTS_API PlayerController : public NativeScript
	{
	public:
		PlayerController(const Entity& e, const SharedApplication& app);
		virtual ~PlayerController(){};
		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;

	private:
		float mSpeed;
		ECS::Handle<TransformComponent> mTransform;
	};

	OE_DECLARE_CREATOR(PlayerController);
} // namespace Orbital
