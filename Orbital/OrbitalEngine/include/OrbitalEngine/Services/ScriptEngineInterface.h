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
	class ORBITAL_ENGINE_API ScriptEngineInterface : public ServiceInterface
	{
	public:
		ScriptEngineInterface();
		ScriptEngineInterface(const SharedApplication& app);

		/**
		 * @brief Initializes the interface
		 *
		 * @todo Rename to InitializeInterface
		 */
		void InitializeInterface();

		/**
		 * @brief Registers the library
		 *
		 * Loads the library of name `libraryName`
		 *
		 * @param libraryName [name of the library]
		 */
		void RegisterLibrary(std::string_view libraryName);

		/**
		 * @brief Registers the script
		 *
		 * Loads the script of name `scriptName` from the appropriate library
		 *
		 * @param scriptName [The name of the script]
		 */
		void RegisterScript(std::string_view libraryName, const std::string& scriptName);

		/**
		 * @brief Loads the registered scripts
		 *
		 * Opens the library and loads the scripts
		 */
		void LoadLibraries();

		/**
		 * @brief Recompiles the libraries
		 *
		 * Closes the libraries, recompile them, and calls LoadLibraries()
		 *
		 * @return [true if compilation succeeded]
		 */
		auto Recompile() -> bool;

		/**
		 * @brief Returns true if the last compilation succeeded
		 *
		 * @return [true if the compilation succeeded]
		 */
		auto LastCompilationSucceeded() -> bool;

		/**
		 * @brief Creates a script
		 *
		 * @param scriptName : The name of the script
		 * @param e : The entity that will contain the script
		 * @return NativeScript* : Raw pointer to the script
		 */
		auto CreateScript(const std::string& scriptName, const Entity& e)
			-> NativeScript*;

		/**
		 * @brief Returns the ScriptsLibraryLoader instance from the Application
		 *
		 * @return [the ScriptsLibraryLoader instance]
		 */
		auto Get() const -> WeakRef<ScriptsLibraryLoader> { return mInstance; }

	private:
		WeakRef<ScriptsLibraryLoader> mInstance;
	};

	OCREATE_SERVICE(ScriptEngine);

} // namespace Orbital
