#include "OrbitalEngine/DebugLayer.h"
#include "OrbitalEngine/Settings.h"
#include "OrbitalEngine/Statistics.h"
#include "OrbitalImGui/Context.h"
#include "OrbitalImGui/ImGuiContext.h"
#include "OrbitalImGui/Core.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Files.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	DebugLayer::DebugLayer(const SharedApplication& app) : DebugLayerServices(app)
	{
		DebugLayerServices::InitializeServices();
	}

	void DebugLayer::initialize(Window* window)
	{
		Gui::InitializeImGui(window);
	}

	void DebugLayer::beginFrame()
	{
		Gui::BeginFrame();

		showStatistics();

		if (mShowDemo)
			ImGui::ShowDemoWindow(&mShowDemo);

		if (mShowSettings)
			showSettings();
	}

	void DebugLayer::endFrame()
	{
		Gui::EndFrame();
	}

	void DebugLayer::terminate()
	{
		Gui::TerminateImGui();
	}

	void DebugLayer::showStatistics()
	{
		if (mFPSmeasurementCount != 50)
		{
			mFPSmeasurementCount += 1;
			mFPSsum += Statistics.Get<float>(Statistic::FPS);
		}
		else
		{
			mAverageFPS = mFPSsum / (float)mFPSmeasurementCount;
			mFPSmeasurementCount = 0;
			mFPSsum = 0.0f;
		}

		ImGui::Begin("Statistics");
		ImGui::Checkbox("Demo Window", &mShowDemo);
		ImGui::Checkbox("Settings", &mShowSettings);

		ImGui::Text("%.2f ms/frame", Statistics.Get<float>(Statistic::Frametime));
		ImGui::Text("%.2f FPS", Statistics.Get<float>(Statistic::FPS));
		ImGui::Text("%.2f AverageFPS", mAverageFPS);
		ImGui::Text("%d Draw calls", Statistics.Get<unsigned int>(Statistic::DrawCalls));
		ImGui::End();
	}

	void DebugLayer::showSettings()
	{
		ImGui::Begin("Settings", &mShowSettings);

		{
			const char* titles[] = { "Full screen", "Windowed" };
			const Orbital::Window::Mode values[] = {
				Window::Mode::FullScreen,
				Window::Mode::Windowed,
			};

			int current = (int)Settings.Get<Orbital::Window::Mode>(Setting::WindowMode);
			ImGui::Combo("Window mode", &current, titles, IM_ARRAYSIZE(titles));
			Settings.Set(Setting::WindowMode, (Orbital::Window::Mode)values[current]);
		}

		{
			char buffer[60] = "";
			strcpy(buffer, Settings.Get<std::string>(Setting::WindowTitle).c_str());
			ImGui::InputText("Game title", buffer, IM_ARRAYSIZE(buffer));
			Settings.Set(Setting::WindowTitle, std::string(buffer));
		}

		ImGui::ShowFontSelector("Font");

		{
			float fov = Settings.Get<float>(Setting::FOV);
			ImGui::DragFloat("FOV", &fov, 1.0f, 30.0f, 120.0f);
			Settings.Set(Setting::FOV, fov);
		}

		{
			float mouseSensitivity = Settings.Get<float>(Setting::MouseSensitivity);
			ImGui::DragFloat("Mouse Sensitivity", &mouseSensitivity, 1.0f, 0.0f, 500.0f);
			Settings.Set(Setting::MouseSensitivity, mouseSensitivity);
		}

		//{ This should set window resolution, not size
		//	const char* titles[] = { "800x600", "1280x720" };

		//	static int currentWidth = (int)Settings.Get<unsigned int>(Setting::WindowWidth);
		//	static int currentHeight = (int)Settings.Get<unsigned int>(Setting::WindowHeight);

		//	ImGui::Text("Window resolution");
		//	ImGui::InputInt("Width", &currentWidth);
		//	ImGui::InputInt("Height", &currentHeight);

		//	if (ImGui::Button("Apply"))
		//	{
		//		Settings.Set(Setting::WindowWidth, (unsigned int)currentWidth);
		//		Settings.Set(Setting::WindowHeight, (unsigned int)currentHeight);
		//	}
		//}

		ImGui::End();
	}
} // namespace Orbital
