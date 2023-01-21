#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"

namespace Orbital
{
	using NativeScriptManagerServices = Services<AccessScriptEngine>;

	class ORBITAL_ENGINE_API NativeScriptManager : public Component, public NativeScriptManagerServices
	{
	public:
		NativeScriptManager(const Component::InitArgs& c, const SharedApplication& app);
		~NativeScriptManager();

		void clear();

		void onLoad();
		void onStart();
		void onPreUpdate(const Time& dt);
		void onUpdate(const Time& dt);
		void onPostUpdate(const Time& dt);
		void onCleanUp();

		void push(std::string_view name, const Entity& e);

		template <typename T>
		auto get() -> WeakRef<T>
		{
			for (auto& [name, script] : mScripts)
			{
				if (name == T::GetName())
				{
					return std::static_pointer_cast<T>(script);
				}
			}
			return WeakRef<T>();
		}

		template <typename T>
		void remove()
		{
			auto iterator = mScripts.find(T::GetName());
			if (iterator != mScripts.end())
			{
				mScripts.erase(iterator);
			}
		}

		[[nodiscard]] auto getScriptNames() const -> std::vector<std::string>;

	private:
		std::unordered_map<std::string, Ref<NativeScript>> mScripts;
	};
} // namespace Orbital
