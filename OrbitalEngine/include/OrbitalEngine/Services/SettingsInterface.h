#pragma once

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/SettingsManager.h"

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
		void Initialize();

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

	private:
		WeakRef<SettingsManager> mInstance;
	};

	OCREATE_SERVICE(Settings);
} // namespace Orbital
