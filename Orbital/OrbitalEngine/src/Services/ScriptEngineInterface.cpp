#include "OrbitalEngine/Services/ScriptEngineInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/SceneManager.h"

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
		Logger::Log("Recompiling scripts");
		mApp.lock()->getSceneManager().lock()->terminate();

		bool compilationSucceeded = mInstance.lock()->recompile();

		if (compilationSucceeded)
		{
 			// TODO make a script specific function
			mApp.lock()->onInitialize();
		}

		return compilationSucceeded;
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
