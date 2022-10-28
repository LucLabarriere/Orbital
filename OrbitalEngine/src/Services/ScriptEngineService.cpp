#include "OrbitalEngine/Services/ScriptEngineService.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
	ScriptEngineInterface::ScriptEngineInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void ScriptEngineInterface::Initialize()
	{
		mInstance = mApp->getLibraryLoader();
	}

	bool ScriptEngineInterface::LastCompilationSucceeded()
	{
		return mInstance->lastCompilationSucceeded();
	}

	void ScriptEngineInterface::RegisterScript(const std::string& scriptName)
	{
		mInstance->registerScript(scriptName);
	}

	NativeScript* ScriptEngineInterface::CreateScript(const std::string& scriptName, const Entity& e)
	{
		return mInstance->createScript(scriptName, e);
	}

	bool ScriptEngineInterface::Reload()
	{
		return mInstance->reload();
	}
} // namespace Orbital
