#pragma once

#include "OrbitalEngine/Services/ScenesInterface.h"
#include "OrbitalEngine/Services/SettingsInterface.h"
#include "OrbitalEngine/Services/StatisticsInterface.h"
#include "OrbitalEngine/Services/ScriptEngineInterface.h"
#include "OrbitalEngine/Services/ECSInterface.h"

namespace Orbital
{
	class Window;

	using DebugLayerServices = Services<AccessScenes, AccessStatistics, AccessSettings, AccessScriptEngine, AccessECS>;

	class ORBITAL_ENGINE_API DebugLayer : public DebugLayerServices
	{
	public:
		DebugLayer(const SharedApplication& app);
		~DebugLayer() = default;

		void initialize(UniqueHandle<Window> window);
		void beginFrame();
		void endFrame();
		void terminate();

	private:
		void showStatistics();
		void showSettings();
		void showSceneControls();
		void showEntities();

	private:
		float mFPSsum = 0.0f;
		float mAverageFPS = 0.0f;
		size_t mFPSmeasurementCount = 0;
		bool mShowDemo = false;
		bool mShowSettings = false;
	};
} // namespace Orbital
