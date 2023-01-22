#include "OrbitalEngine/Services/ScriptEngineInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
	ScriptEngineInterface::ScriptEngineInterface() : ServiceInterface()
	{
	}

	ScriptEngineInterface::ScriptEngineInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void ScriptEngineInterface::InitializeInterface()
	{
		mInstance = mApp.lock()->getLibraryLoader();
	}

	void ScriptEngineInterface::RegisterLibrary(std::string_view libraryName)
	{
		return mInstance.lock()->registerLibrary(libraryName);
	}

	void ScriptEngineInterface::RegisterScript(
		std::string_view libraryName, const std::string& scriptName
	)
	{
		return mInstance.lock()->registerScript(libraryName, scriptName);
	}

	void ScriptEngineInterface::LoadLibraries()
	{
		return mInstance.lock()->loadLibraries();
	}

	auto ScriptEngineInterface::Recompile() -> bool
	{
		return mInstance.lock()->recompile();
	}

	auto ScriptEngineInterface::LastCompilationSucceeded() -> bool
	{
		return mInstance.lock()->lastCompilationSucceeded();
	}

	auto ScriptEngineInterface::CreateScript(
		const std::string& scriptName, const Entity& e
	) -> NativeScript*
	{
		return mInstance.lock()->createScript(scriptName, e);
	}
} // namespace Orbital
