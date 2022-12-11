#pragma once

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class ScriptsLibraryLoader;
	class NativeScript;

	class OENGINE_API ScriptEngineInterface : public ServiceInterface
	{
	public:
		ScriptEngineInterface();
		ScriptEngineInterface(const SharedApplication& app);
		void Initialize();

		bool LastCompilationSucceeded();
		void RegisterScript(const std::string& scriptName);
		NativeScript* CreateScript(const std::string& scriptName, const Entity& e);
		bool Reload();

	private:
		std::weak_ptr<ScriptsLibraryLoader> mInstance;
	};

	OCREATE_SERVICE(ScriptEngine);

} // namespace Orbital
