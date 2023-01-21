#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Settings.h"

namespace Orbital
{
	enum class Setting;

	class ORBITAL_ENGINE_API SettingManager
	{
	public:
		SettingManager();

		template <typename T>
		T& getMut(Setting setting)
		{
			std::any& s = mSettings[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			mRequestedCallbacks.emplace(setting);
			return std::any_cast<T&>(s);
		}

		template <typename T>
		const T& get(Setting setting) const
		{
			const std::any& s = mSettings[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			return std::any_cast<const T&>(s);
		}

		template <typename T>
		T& getMut(const std::string& setting)
		{
			for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			{
				if (setting.c_str() == SettingNames[i])
				{
					return getMut<T>(mSettings[i]);
				}
			}
			Orbital::Raise("Setting " + setting + " was not found");
		}

		template <typename T>
		const T& get(const std::string& setting) const
		{
			for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			{
				if (setting.c_str() == SettingNames[i])
				{
					return get<T>(mSettings[i]);
				}
			}
			Orbital::Raise("Setting " + setting + " was not found");
		}

		template <typename T>
		void set(Setting setting, const T& value)
		{
			const auto& constV = get<T>(setting);

			if (constV != value)
			{
				getMut<T>(setting) = value;
			}
		}

		void setCallback(Setting setting, const std::function<void()>& callback)
		{
			mCallbacks[(size_t)setting] = callback;
		}

		void handleCallbacks();

	private:
		std::vector<std::any> mSettings;
		std::vector<std::function<void()>> mCallbacks;
		std::unordered_set<Setting> mRequestedCallbacks;
	};
} // namespace Orbital
