#pragma once

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/SettingManager.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API SettingsInterface : public ServiceInterface
	{
	public:
		SettingsInterface();
		SettingsInterface(const SharedApplication& app);

		/**
		 * @brief Initializes the interface
		 *
		 * @todo Rename to InitializeInterface
		 */
		void InitializeInterface();

		template <typename T>
		auto GetMut(Setting setting) -> T&
		{
			return mInstance.lock()->getMut<T>(setting);
		}

		template <typename T>
		auto Get(Setting setting) const -> const T&
		{
			return mInstance.lock()->get<T>(setting);
		}

		template <typename T>
		auto GetMut(const std::string& setting) -> T&
		{
			return mInstance.lock()->getMut<T>(setting);
		}

		template <typename T>
		auto Get(const std::string& setting) const -> const T&
		{
			return mInstance.lock()->get<T>(setting);
		}

		template <typename T>
		void Set(Setting setting, const T& value)
		{
			mInstance.lock()->set(setting, value);
		}

	private:
		WeakRef<SettingManager> mInstance;
	};

	OCREATE_SERVICE(Settings);
} // namespace Orbital
