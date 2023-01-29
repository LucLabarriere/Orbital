#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	template <typename Obj>
	class ORBITAL_ENGINE_API AnyManager
	{
	public:
		AnyManager();

		template <typename T>
		auto getMut(Obj obj) -> T&
		{
			std::any& o = mObjects[(size_t)obj];

			try
			{
				auto& value = std::any_cast<T&>(o);
				return value;
			}

			catch (const std::bad_any_cast& e)
			{
				Orbital::Assert(
					o.type() == typeid(T),
					std::string("The \"") + typeid(Obj).name() + "\" \"" + SettingNames[(size_t)setting] +
						"\" was accessed using the incorrect type : " + typeid(T).name()
				);
			}

			return std::any_cast<T&>(s);
		}

		template <typename T>
		auto get(Setting setting) const -> const T&
		{
			const std::any& s = mObjects[(size_t)setting];

			try
			{
				const auto& value = std::any_cast<const T&>(s);
				return value;
			}
			catch (const std::bad_any_cast& e)
			{
				Orbital::Assert(
					s.type() == typeid(T),
					std::string("The setting \"") + SettingNames[(size_t)setting] +
						"\" was accessed using the incorrect type : " + typeid(T).name()
				);
			}

			return std::any_cast<const T&>(s);
		}

		template <typename T>
		auto getMut(const std::string& setting) -> T&
		{
			for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			{
				if (setting.c_str() == SettingNames[i])
				{
					return getMut<T>(mObjects[i]);
				}
			}
			Orbital::Raise("Setting " + setting + " was not found");
		}

		template <typename T>
		auto get(const std::string& setting) const -> const T&
		{
			for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			{
				if (setting.c_str() == SettingNames[i]) { return get<T>(mObjects[i]); }
			}
			Orbital::Raise("Setting " + setting + " was not found");
		}

		template <typename T>
		void set(Setting setting, const T& value)
		{
			const auto& constV = get<T>(setting);

			if (constV != value) { getMut<T>(setting) = value; }
		}

		void setCallback(Setting setting, const std::function<void()>& callback)
		{
			mCallbacks[(size_t)setting] = callback;
		}

		void handleCallbacks();

	private:
		std::array<std::any, (size_t)Setting::SIZE> mObjects;
		std::vector<std::function<void()>> mCallbacks;
		std::unordered_set<Setting> mRequestedCallbacks;
	};
}
