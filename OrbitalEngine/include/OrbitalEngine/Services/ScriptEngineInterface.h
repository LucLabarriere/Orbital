#pragma once

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class ScriptsLibraryLoader;
	class NativeScript;

	/**
	 * @class ScriptEngineInterface
	 * @brief Interface to the script engine
	 */
	class OENGINE_API ScriptEngineInterface : public ServiceInterface
	{
	public:
		ScriptEngineInterface();
		ScriptEngineInterface(const SharedApplication& app);
		/**
		 * @brief Initializes the interface
		 */
		void Initialize();

		WeakRef<ScriptsLibraryLoader> Get() const { return mInstance; }


		/**
		 * @brief Sets the current scripts library
		 *
		 * @param libraryName [Name of the library]
		 */
		void SetLibrary(const std::string& libraryName);

		/**
		 * @brief Returns true if the last compilation succeeded
		 *
		 * @return bool
		 */
		bool LastCompilationSucceeded();

		/**
		 * @brief Registers the script
		 *
		 * Loads the string of name `scriptName` from the Scripts library
		 *
		 * @param scriptName : The name of the script
		 */
		void RegisterScript(const std::string& scriptName);

		/**
		 * @brief Creates a script
		 *
		 * @param scriptName : The name of the script
		 * @param e : The entity that will contain the script
		 * @return NativeScript* : Raw pointer to the script
		 */
		NativeScript* CreateScript(const std::string& scriptName, const Entity& e);

		/**
		 * @brief Reloads the Scripts shared library
		 *
		 * @return bool : True is the compilation succeeded
		 */
		bool Reload();

	private:
		WeakRef<ScriptsLibraryLoader> mInstance;
	};

	OCREATE_SERVICE(ScriptEngine);

} // namespace Orbital
