#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ScriptHandle.h"
#include "OrbitalEngine/SharedApplication.h"

namespace Orbital
{
	class NativeScript;
	class Entity;
	typedef NativeScript* CreateNativeScript_t(
		const Entity& e, const SharedApplication& app
	);

	class Library
	{
	public:
		Library(std::string_view libraryName);

		auto open() -> bool;
		void load();
		auto compile() -> bool;
		void close();
		void registerScript(std::string_view scriptName);

		auto getLibraryName() const -> const std::string& { return mLibraryName; }

		auto getLibraryFileName() const -> const std::string& { return mLibraryFileName; }

		auto begin() -> std::vector<ScriptHandle>::iterator { return mScripts.begin(); }

		auto end() -> std::vector<ScriptHandle>::iterator { return mScripts.end(); }

	private:
		void* mHandle = nullptr;
		bool mSucceeded = true;

		std::string mLibraryName = "";
		std::string mLibraryFileName = "";
		std::string mLibraryPath = "";

		std::vector<ScriptHandle> mScripts;
	};
} // namespace Orbital
