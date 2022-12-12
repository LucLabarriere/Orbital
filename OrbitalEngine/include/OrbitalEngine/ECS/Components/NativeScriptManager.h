#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"

namespace Orbital
{
	using NativeScriptManagerServices = Services<AccessScriptEngine>;

	class OENGINE_API NativeScriptManager : public NativeScriptManagerServices
	{
	public:
		NativeScriptManager(const SharedApplication& app);
		~NativeScriptManager();

		void clear();

		void onLoad();
		void onStart();
		void onPreUpdate(const Time& dt);
		void onUpdate(const Time& dt);
		void onCleanUp();

		void push(const std::string& name, const Entity& e);

		template <typename T>
		std::weak_ptr<T> get()
		{
			for (auto& [name, script] : mScripts)
			{
				if (name == T::GetName())
				{
					return std::static_pointer_cast<T>(script);
				}
			}
			return std::weak_ptr<T>();
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

		std::vector<std::string> getScriptNames() const;

	private:
		std::unordered_map<std::string, std::shared_ptr<NativeScript>> mScripts;
	};
} // namespace Orbital
