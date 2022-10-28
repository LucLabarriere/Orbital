#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Entity.h"
#include "OrbitalEngine/Services/ApplicationServices.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalTools/Time.h"

#define OE_DECLARE_CREATOR(CreatorName)                                                                                \
	extern "C" OSCRIPTS_API NativeScript* Create##CreatorName(const Entity& e, const SharedApplication& app)

// TODO Change names here DEFINE, DECLARE, IMPLEMENT ?

#define OE_DEFINE_CREATOR(CreatorName)                                                                                 \
	NativeScript* Create##CreatorName(const Entity& e, const SharedApplication& app)                                   \
	{                                                                                                                  \
		return new CreatorName(e, app);                                                                                \
	}

namespace Orbital
{
	using NativeScriptServices = Services<AccessECS, AccessPhysics, AccessRenderer, AccessScenes>;

	class OENGINE_API NativeScript : public Entity, public NativeScriptServices
	{
	public:
		NativeScript(const Entity& e, const SharedApplication& app);
		virtual ~NativeScript()
		{
		}

		virtual void onLoad(){};
		virtual void onStart(){};
		virtual void onUpdate(const Time& dt){};
		virtual void onCleanUp(){};
	};

	typedef NativeScript* CreateNativeScript_t(const Entity& e, const SharedApplication& app);
} // namespace Orbital
