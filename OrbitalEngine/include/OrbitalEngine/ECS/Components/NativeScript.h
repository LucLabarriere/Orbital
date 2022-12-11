#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/PhysicsInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"

#include "OrbitalInputs/Core.h"

#define OE_DECLARE_CREATOR(ScriptName)                                                                                 \
	template <>                                                                                                        \
	inline const ScriptName& SafeHandle<ScriptName>::operator*() const                                     \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<NativeScriptManager>();                                                        \
		auto script = scriptManager->get<ScriptName>().lock();                                                   \
                                                                                                                       \
		return *script;                                                                                                \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline bool SafeHandle<ScriptName>::isValid() const                                                          \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<NativeScriptManager>();                                                        \
		auto script = scriptManager->get<ScriptName>();                                                          \
		return !script.expired();                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline void Entity::remove<ScriptName>()                                                                     \
	{                                                                                                                  \
		assert(get<ScriptName>().isValid() == true && "Trying to remove a non existing component");              \
		auto manager = get<NativeScriptManager>();                                                                     \
		manager->remove<ScriptName>();                                                                           \
	}                                                                                                                  \
	template <>                                                                                                        \
	inline Orbital::SafeHandle<ScriptName> Orbital::Entity::push<ScriptName>()                                         \
	{                                                                                                                  \
		pushNativeScript(ScriptName::GetName());                                                                       \
		return SafeHandle<ScriptName>(mEntityID, mManager);                                                            \
	}                                                                                                                  \
	extern "C" OSCRIPTS_API NativeScript* Create##ScriptName(const Entity& e, const SharedApplication& app)

// TODO Change names here DEFINE, DECLARE, IMPLEMENT ?

#define OE_DEFINE_CREATOR(ScriptName)                                                                                  \
	NativeScript* Create##ScriptName(const Entity& e, const SharedApplication& app)                                    \
	{                                                                                                                  \
		return new ScriptName(e, app);                                                                                 \
	}

#define OE_SCRIPT_NAME(ScriptName)                                                                                     \
	static inline std::string GetName()                                                                                       \
	{                                                                                                                  \
		return #ScriptName;                                                                                            \
	}

namespace Orbital
{
	using NativeScriptServices = Services<AccessECS, AccessRenderer, AccessScenes, AccessPhysics>;

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
