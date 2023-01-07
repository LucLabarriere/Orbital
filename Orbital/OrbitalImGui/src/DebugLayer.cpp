#include "OrbitalImGui/DebugLayer.h"
#include "OrbitalImGui/Context.h"
#include "OrbitalRenderer/Window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Orbital
{
	namespace Gui
	{
		DebugLayer::DebugLayer()
		{
		}

		void DebugLayer::initialize(Window* window)
		{
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			(void)io;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

			ImGui::StyleColorsDark();
			// ImGui::StyleColorsLight();

			ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNativeWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 420 core");
		}

		void DebugLayer::beginFrame()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (mShowDemoWindow)
				ImGui::ShowDemoWindow(&mShowDemoWindow);

			showStatistics();
		}

		void DebugLayer::endFrame()
		{
			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}

		void DebugLayer::terminate()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void DebugLayer::showStatistics()
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Application statistics");
			ImGui::Checkbox("Demo Window", &mShowDemoWindow);

			ImGui::Text(
				"%.2f ms/frame",
				1000.0f / ImGui::GetIO().Framerate
			);
			ImGui::Text(
				"%.2f FPS",
				ImGui::GetIO().Framerate
			);
			ImGui::End();
		}
	} // namespace Gui
} // namespace Orbital
