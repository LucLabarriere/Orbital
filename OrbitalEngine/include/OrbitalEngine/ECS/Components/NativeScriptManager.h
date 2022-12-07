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
		void onUpdate(const Time& dt);
		void onCleanUp();

		void push(const std::string& name, const Entity& e);
		std::vector<std::string> getScriptNames() const;

	private:
		std::unordered_map<std::string, NativeScript*> mScripts;
	};
} // namespace Orbital
