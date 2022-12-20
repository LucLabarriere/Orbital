#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/NativeScript.h"
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
		void setLibraryName(const std::string& libraryName)
		{
			mLibraryName = libraryName;
#ifdef _WIN32
			mLibraryFileName = libraryName + ".dll";
#else // Linux
			mLibraryFileName = "lib" + libraryName + ".so";
#endif
		}

	private:
		void saveScriptNames();

	private:
		friend class ScriptEngineInterface;

		void* mLibrary = nullptr;
		std::unordered_map<std::string, CreateNativeScript_t*> mCreators;
		std::unordered_set<std::string> mScriptNames;
		bool mSucceeded = false;
		std::string mLibraryName = "";
		std::string mLibraryFileName = "";
	};
} // namespace Orbital
