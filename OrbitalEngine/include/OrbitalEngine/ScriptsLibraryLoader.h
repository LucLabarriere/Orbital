#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
	using ScriptsLibraryLoaderServices = Services<>;

	class OENGINE_API ScriptsLibraryLoader : public ScriptsLibraryLoaderServices
	{
	public:
		ScriptsLibraryLoader(const SharedApplication& app);
		virtual ~ScriptsLibraryLoader()
		{
			LOGFUNC();
		}

		void initialize();
		void terminate();

		void open();
		void close();
		bool reload();
		void registerScript(const std::string& scriptName);
		NativeScript* createScript(const std::string& scriptName, const Entity& e);
		bool recompileLibrary();
		bool lastCompilationSucceeded() const
		{
			return mSucceeded;
		}

	private:
		void saveScriptNames();

	private:
		friend class ScriptEngineInterface;

		void* mLibrary = nullptr;
		std::unordered_map<std::string, CreateNativeScript_t*> mCreators;
		std::unordered_set<std::string> mScriptNames;
		bool mSucceeded = true;
	};
} // namespace Orbital
