#pragma once

#include "OrbitalEngine/SharedApplication.h"

namespace Orbital
{
	class NativeScript;
	class Entity;
	typedef NativeScript* CreateNativeScript_t(const Entity& e, const SharedApplication& app);

	class ScriptHandle
	{
	public:
		ScriptHandle(const std::string& name) : mName(name)
		{
		}

		const std::string& getName() const
		{
			return mName;
		}

		NativeScript* create(const Entity& e, const SharedApplication& app)
		{
			return mCreator(e, app);
		}

		CreateNativeScript_t* getCreator() const
		{
			return mCreator;
		}

		void setCreator(CreateNativeScript_t* creator)
		{
			mCreator = creator;
		}

	private:
		std::string mName = "";
		CreateNativeScript_t* mCreator = nullptr;
	};
} // namespace Orbital
