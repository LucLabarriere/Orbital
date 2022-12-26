#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/SharedApplication.h"
#include "OrbitalEngine/ScriptHandle.h"

namespace Orbital
{
	class NativeScript;
	class Entity;
	typedef NativeScript* CreateNativeScript_t(const Entity& e, const SharedApplication& app);

	class Library
	{
	public:
		Library(const std::string& libraryName);

		bool open();
		void load();
		void close();
		void registerScript(const std::string& scriptName);

		const std::string& getLibraryName() const
		{
			return mLibraryName;
		}

		const std::string& getLibraryFileName() const
		{
			return mLibraryFileName;
		}

		std::vector<ScriptHandle>::iterator begin()
		{
			return mScripts.begin();
		}

		std::vector<ScriptHandle>::iterator end()
		{
			return mScripts.end();
		}

	private:
		void* mHandle = nullptr;
		bool mSucceeded = true;

		std::string mLibraryName = "";
		std::string mLibraryFileName = "";
		std::string mLibraryPath = "";

		std::vector<ScriptHandle> mScripts;
	};
} // namespace Orbital
