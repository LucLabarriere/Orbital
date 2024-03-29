#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"

namespace Orbital
{
	NativeScriptManager::NativeScriptManager(
		const Component::InitArgs& c, const SharedApplication& app
	)
		: Component(c), NativeScriptManagerServices(app)
	{
		NativeScriptManagerServices::InitializeServices();
	}

	NativeScriptManager::~NativeScriptManager()
	{
		clear();
	}

	void NativeScriptManager::clear()
	{
		for (auto& [name, script] : mScripts)
		{
			// If nullptr, the clearing was already done
			if (script == nullptr) break;

			script->onCleanUp();
			script.reset();
			script = nullptr;
		}

		mScripts.clear();
	}

	void NativeScriptManager::onLoad()
	{
		for (auto& [name, script] : mScripts)
		{
			script->onLoad();
		}
	}

	void NativeScriptManager::onStart()
	{
		for (auto& [name, script] : mScripts)
		{
			script->onStart();
		}
	}

	void NativeScriptManager::onPreUpdate(const Time& dt)
	{
		for (auto& [name, script] : mScripts)
		{
			script->onPreUpdate(dt);
		}
	}

	void NativeScriptManager::onUpdate(const Time& dt)
	{
		for (auto& [name, script] : mScripts)
		{
			script->onUpdate(dt);
		}
	}

	void NativeScriptManager::onPostUpdate(const Time& dt)
	{
		for (auto& [name, script] : mScripts)
		{
			script->onPostUpdate(dt);
		}
	}

	void NativeScriptManager::onCleanUp()
	{
		for (auto& [name, script] : mScripts)
		{
			script->onCleanUp();
		}
	}

	void NativeScriptManager::push(std::string_view name, const Entity& e)
	{
		auto script = ScriptEngine.CreateScript(std::string(name), e);
		mScripts.emplace(name, script);
		script->onCreate();
	}

	auto NativeScriptManager::getScriptNames() const -> std::vector<std::string>
	{
		std::vector<std::string> names(mScripts.size());

		size_t i = 0;

		for (auto& [name, script] : mScripts)
		{
			names[i] = name;
			i++;
		}

		return names;
	}
} // namespace Orbital
