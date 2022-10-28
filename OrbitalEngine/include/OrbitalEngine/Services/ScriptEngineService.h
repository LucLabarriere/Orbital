#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Entity.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class ScriptsLibraryLoader;
	class NativeScript;

	class OENGINE_API ScriptEngineInterface : public ServiceInterface
	{
	public:
		ScriptEngineInterface(const SharedApplication& app);
		void Initialize();

		bool LastCompilationSucceeded();
		void RegisterScript(const std::string& scriptName);
		NativeScript* CreateScript(const std::string& scriptName, const Entity& e);
		bool Reload();

	private:
		ScriptsLibraryLoader* mInstance = nullptr;
	};
} // namespace Orbital
