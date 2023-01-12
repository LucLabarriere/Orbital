#pragma once

#include "OrbitalEngine/Services/SettingsInterface.h"
#include "OrbitalEngine/Services/StatisticsInterface.h"

namespace Orbital
{
	class Window;

	using DebugLayerServices = Services<AccessStatistics, AccessSettings>;

	class DebugLayer : public DebugLayerServices
	{
	public:
		DebugLayer(const SharedApplication& app);
		~DebugLayer(){};

		void initialize(Window* window);
		void beginFrame();
		void endFrame();
		void terminate();

	private:
		void showStatistics();
		void showSettings();

	private:
		float mFPSsum = 0.0f;
		float mAverageFPS = 0.0f;
		size_t mFPSmeasurementCount = 0;
		bool mShowDemo = false;
		bool mShowSettings = false;
	};
} // namespace Orbital