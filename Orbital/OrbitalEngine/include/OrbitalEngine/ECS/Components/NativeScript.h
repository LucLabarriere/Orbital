#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"

#include "OrbitalInputs/Core.h"

#define OE_DECLARE_CREATOR(API, Namespace, ScriptName)                                                                 \
	template <>                                                                                                        \
	inline auto Orbital::SafeHandle<Namespace::ScriptName>::operator*() const->const Namespace::ScriptName&            \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<Orbital::NativeScriptManager>();                                               \
		auto script = scriptManager->get<Namespace::ScriptName>().lock();                                              \
                                                                                                                       \
		return *script;                                                                                                \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline auto Orbital::SafeHandle<Namespace::ScriptName>::isValid() const->bool                                      \
	{                                                                                                                  \
		auto entity = mManager.lock()->getEntity(mEntityID);                                                           \
		auto scriptManager = entity.get<Orbital::NativeScriptManager>();                                               \
		auto script = scriptManager->get<Namespace::ScriptName>();                                                     \
                                                                                                                       \
		return !script.expired();                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	template <>                                                                                                        \
	inline auto Orbital::Entity::remove<Namespace::ScriptName>()->void                                                 \
	{                                                                                                                  \
		Orbital::Assert(get<Namespace::ScriptName>().isValid() == true, "Trying to remove a non existing component");  \
		auto manager = get<Orbital::NativeScriptManager>();                                                            \
		manager->remove<Namespace::ScriptName>();                                                                      \
	}                                                                                                                  \
	template <>                                                                                                        \
	inline auto Orbital::Entity::push<Namespace::ScriptName>()->Orbital::SafeHandle<Namespace::ScriptName>             \
	{                                                                                                                  \
		pushNativeScript(Namespace::ScriptName::GetName());                                                            \
		return Orbital::SafeHandle<Namespace::ScriptName>(mEntityID, mManager);                                        \
	}                                                                                                                  \
                                                                                                                       \
	extern "C" API auto Create##ScriptName(const Orbital::Entity& e)->Orbital::NativeScript*

// TODO Change names here DEFINE, DECLARE, IMPLEMENT ?

#define OE_DEFINE_CREATOR(Namespace, ScriptName)                                                                       \
	auto Create##ScriptName(const Orbital::Entity& e)->Orbital::NativeScript*                                          \
	{                                                                                                                  \
		return new Namespace::ScriptName(e);                                                                           \
	}

#define OE_SCRIPT_NAME(ScriptName)                                                                                     \
	static inline auto GetName()->std::string                                                                          \
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
	class ORBITAL_ENGINE_API NativeScript : public Entity
	{
	public:
		NativeScript(const Entity& e);
		~NativeScript() override = default;

		/**
		 * @brief Called upon loading the scene
		 */
		virtual void onLoad(){};

		/**
		 * @brief Called upon starting the scene
		 */
		virtual void onStart(){};

		/**
		 * @brief Called upon creating the script
		 */
		virtual void onCreate(){};

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
		 * @brief Called upon post updating the scene
		 *
		 * @param dt : Deltatime
		 */
		virtual void onPostUpdate(const Time& dt){};

		/**
		 * @brief Called upon cleaning up the scene
		 */
		virtual void onCleanUp(){};
	};

	using CreateNativeScript_t = NativeScript *(const Entity &, const SharedApplication &);
} // namespace Orbital
