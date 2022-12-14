#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"

#include "OrbitalInputs/Core.h"

#define OE_DECLARE_CREATOR(ScriptName)                                                                                 \
	template <>                                                                                                        \
	inline const ScriptName& SafeHandle<ScriptName>::operator*() const                                                 \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<NativeScriptManager>();                                                        \
		auto script = scriptManager->get<ScriptName>().lock();                                                         \
                                                                                                                       \
		return *script;                                                                                                \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline bool SafeHandle<ScriptName>::isValid() const                                                                \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<NativeScriptManager>();                                                        \
		auto script = scriptManager->get<ScriptName>();                                                                \
		return !script.expired();                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline void Entity::remove<ScriptName>()                                                                           \
	{                                                                                                                  \
		Orbital::Assert(get<ScriptName>().isValid() == true, "Trying to remove a non existing component");                    \
		auto manager = get<NativeScriptManager>();                                                                     \
		manager->remove<ScriptName>();                                                                                 \
	}                                                                                                                  \
	template <>                                                                                                        \
	inline Orbital::SafeHandle<ScriptName> Orbital::Entity::push<ScriptName>()                                         \
	{                                                                                                                  \
		pushNativeScript(ScriptName::GetName());                                                                       \
		return SafeHandle<ScriptName>(mEntityID, mManager);                                                            \
	}                                                                                                                  \
                                                                                                                       \
	extern "C" OSCRIPTS_API NativeScript* Create##ScriptName(const Entity& e)

// TODO Change names here DEFINE, DECLARE, IMPLEMENT ?

#define OE_DEFINE_CREATOR(ScriptName)                                                                                  \
	NativeScript* Create##ScriptName(const Entity& e)                                                                  \
	{                                                                                                                  \
		return new ScriptName(e);                                                                                      \
	}

#define OE_SCRIPT_NAME(ScriptName)                                                                                     \
	static inline std::string GetName()                                                                                \
	{                                                                                                                  \
		return #ScriptName;                                                                                            \
	}

namespace Orbital
{
	/**
	 * @class NativeScript
	 * @brief BaseClass for scripts
	 *
	 * It derives from Entity for conveniance
	 */
	class OENGINE_API NativeScript : public Entity
	{
	public:
		NativeScript(const Entity& e);
		virtual ~NativeScript(){};

		/**
		 * @brief Called upon loading the scene
		 */
		virtual void onLoad(){};

		/**
		 * @brief Called upon starting the scene
		 */
		virtual void onStart(){};

		/**
		 * @brief Called upon pre updating the scene
		 *
		 * @param dt : Deltatime
		 */
		virtual void onPreUpdate(const Time& dt){};

		/**
		 * @brief Called upon updating the scene
		 *
		 * @param dt : Deltatime
		 */
		virtual void onUpdate(const Time& dt){};

		/**
		 * @brief Called upon cleaning up the scene
		 */
		virtual void onCleanUp(){};
	};

	typedef NativeScript* CreateNativeScript_t(const Entity& e, const SharedApplication& app);
} // namespace Orbital
