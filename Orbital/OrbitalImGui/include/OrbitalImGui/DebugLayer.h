#pragma once

#include "OrbitalEngine/Services/StatisticsInterface.h"
#include "OrbitalEngine/Services/SettingsInterface.h"

namespace Orbital
{
	class Window;

	namespace Gui
	{
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
			bool mShowDemo = false;
			bool mShowSettings = false;
		};
	} // namespace Gui
} // namespace Orbital
