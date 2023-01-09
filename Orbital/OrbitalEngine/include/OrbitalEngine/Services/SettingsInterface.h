#pragma once

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/SettingManager.h"

namespace Orbital
{
	class OENGINE_API SettingsInterface : public ServiceInterface
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
		T& GetMut(Setting setting)
		{
			return mInstance.lock()->getMut<T>(setting);
		}

		template <typename T>
		const T& Get(Setting setting) const
		{
			return mInstance.lock()->get<T>(setting);
		}

		template <typename T>
		T& GetMut(const std::string& setting)
		{
			return mInstance.lock()->getMut<T>(setting);
		}

		template <typename T>
		const T& Get(const std::string& setting) const
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
