#include "OrbitalEngine/DebugLayer.h"
#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/Settings.h"
#include "OrbitalEngine/Statistics.h"
#include "OrbitalImGui/Context.h"
#include "OrbitalImGui/Core.h"
#include "OrbitalImGui/ImGuiContext.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Files.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	DebugLayer::DebugLayer(const SharedApplication& app) : DebugLayerServices(app)
	{
		DebugLayerServices::InitializeServices();
	}

	void DebugLayer::initialize(UniqueHandle<Window> window)
	{
		Gui::InitializeImGui(window);
	}

	void DebugLayer::beginFrame()
	{
		Gui::BeginFrame();

		showStatistics();

		if (mShowDemo) ImGui::ShowDemoWindow(&mShowDemo);

		if (mShowSettings) showSettings();

		showSceneControls();
		showEntities();
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

		const auto frametime = Statistics.Get<float>(Statistic::Frametime);
		const auto fps = Statistics.Get<float>(Statistic::FPS);
		const auto drawCalls = Statistics.Get<unsigned int>(Statistic::DrawCalls);

		ImGui::Text("%.2f ms/frame", frametime);
		ImGui::Text("%.2f FPS", fps);
		ImGui::Text("%.2f AverageFPS", mAverageFPS);
		ImGui::Text("%d Draw calls", drawCalls);
		ImGui::End();
	}

	void DebugLayer::showSettings()
	{
		ImGui::Begin("Settings", &mShowSettings);

		{
			const std::array<const char*, 2> titles = { "Full screen", "Windowed" };
			const std::array<Orbital::Window::Mode, 2> values = {
				Window::Mode::FullScreen,
				Window::Mode::Windowed,
			};

			int current = (int)Settings.Get<Orbital::Window::Mode>(Setting::WindowMode);

			ImGui::Combo("Window mode", &current, titles.data(), titles.size());
			Settings.Set(Setting::WindowMode, values[current]);
		}

		{
			std::array<char, 60> buffer = { "" };
			strcpy(
				buffer.data(), Settings.Get<std::string>(Setting::WindowTitle).c_str()
			);
			ImGui::InputText("Game title", buffer.data(), buffer.size());
			Settings.Set(Setting::WindowTitle, std::string(buffer.data()));
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

		//	static int currentWidth = (int)Settings.Get<unsigned
		// int>(Setting::WindowWidth); 	static int currentHeight =
		//(int)Settings.Get<unsigned int>(Setting::WindowHeight);

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

	void DebugLayer::showSceneControls()
	{
		auto state = Scenes.GetState();

		auto playButton = [&]()
		{
			if (ImGui::Button("Play")) Scenes.Resume();
		};

		auto pauseButton = [&]()
		{
			if (ImGui::Button("Pause")) Scenes.Pause();
		};

		auto stopButton = [&]()
		{
			if (ImGui::Button("Stop")) Scenes.Reload();
		};

		switch (state)
		{
		case SceneState::Uninitialized:
		{
			Orbital::Raise("Scene not initialized");
			break;
		}
		case SceneState::Running:
		{
			pauseButton();
			stopButton();
			break;
		}
		case SceneState::Paused:
		{
			playButton();
			stopButton();
			break;
		}
		case SceneState::Stoped:
		{
			playButton();
			break;
		}
		}

		if (ImGui::Button("Recompile")) ScriptEngine.Recompile();
	}

	void DebugLayer::showEntities()
	{
		ImGui::Begin("Entities");

		for (const auto& entityID : ECS.Entities())
		{
			ImGui::Text(ECS.GetEntity(entityID).get<Tag>()->data());
		}

		ImGui::End();
	}
} // namespace Orbital
