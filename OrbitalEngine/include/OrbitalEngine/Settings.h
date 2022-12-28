#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	enum class SettingType
	{
		Bool = 0,
		Int,
		UInt,
		Float,
		String,
		SIZE,
	};

	enum class SettingEnum
	{
		ScreenWidth = 0,
		ScreenHeight,
		FOV,
		FullScreen,
		VSync,
		FPSLimit,
		SIZE,
	};

	static const SettingType SettingTypes[] = {
		SettingType::UInt, SettingType::UInt, SettingType::Float,
		SettingType::Bool, SettingType::Bool, SettingType::UInt,
	};
	static_assert(sizeof(SettingTypes) / sizeof(SettingType) == (size_t)SettingEnum::SIZE);

	// Bool = 0,
	// Int,
	// UInt,
	// Float,
	// String,
	// SIZE,

	static const std::type_info* TypeHashes[] = {
		&typeid(bool), &typeid(int), &typeid(unsigned int), &typeid(float), &typeid(const char*),
	};
	static_assert(sizeof(TypeHashes) / sizeof(std::type_info*) == (size_t)SettingType::SIZE);

	template <typename T>
	static constexpr bool SettingTypeMatches(SettingType type)
	{
		return typeid(T) == *TypeHashes[(size_t)type];
	}

	static const char* SettingNames[(size_t)SettingEnum::SIZE] = {
		"ScreenWidth", "ScreenHeight", "FOV", "FullScreen", "VSync", "FPSLimit",
	};
	static_assert(sizeof(SettingNames) / sizeof(const char*) == (size_t)SettingEnum::SIZE);

	union SettingValue
	{
		int i;
		float f;
		bool b;
		unsigned int ui;
		const char* s;
	};

	class Setting
	{
	public:
		Setting(int v) : mValue({ .i = v }), mType(SettingType::Int)
		{
		}
		Setting(float v) : mValue({ .f = v }), mType(SettingType::Float)
		{
		}
		Setting(bool v) : mValue({ .b = v }), mType(SettingType::Bool)
		{
		}
		Setting(unsigned int v) : mValue({ .ui = v }), mType(SettingType::UInt)
		{
		}
		Setting(const char* v) : mValue({ .s = v }), mType(SettingType::String)
		{
		}

		template <typename T>
		void set(const T& value)
		{
			static_assert(SettingTypeMatches<T>(mType));
			static_cast<T>(mValue) = value;
		}

		template <typename T>
		const T& get() const
		{
			static_assert(SettingTypeMatches<T>(mType));
			return static_cast<T>(mValue);
		}

	private:
		SettingValue mValue;
		SettingType mType;
	};

	class Settings
	{
	public:
		Settings() : mSettings()
		{
			mSettings.reserve((size_t)SettingEnum::SIZE);

			mSettings.emplace_back((unsigned int)640); // SCREEN_HEIGHT
			mSettings.emplace_back((unsigned int)480); // SCREEN_WIDTH
			mSettings.emplace_back((float)60.0f);	   // FOV
			mSettings.emplace_back((bool)true);		   // VSYNC
			mSettings.emplace_back((unsigned int)0);   // FPSLimit

			Orbital::Assert(
				mSettings.size() == (size_t)SettingEnum::SIZE, "The settings were not properly initialized"
			);
		}

		template <typename T>
		void set(SettingEnum setting, const T& value)
		{
			mSettings[(size_t)setting].set(value);
		}

		template <typename T>
		const T& get(SettingEnum setting) const
		{
			return mSettings[(size_t)setting].get<T>();
		}

	private:
		std::vector<Setting> mSettings;
	};
} // namespace Orbital
