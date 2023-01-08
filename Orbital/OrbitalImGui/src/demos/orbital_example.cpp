// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context
// creation, etc.) If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "OrbitalImGui/imgui.h"
#include "OrbitalImGui/imgui_impl_glfw.h"
#include "OrbitalImGui/imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalImGui/DebugLayer.h"
#include "OrbitalTools/Files.h"

int main(int argc, char** argv)
{
	Orbital::Files::SetBinaryDir(argv[0]);
	Orbital::LowRenderer lowRenderer;
	lowRenderer.initialize(800, 600);
	Orbital::Window* window = &lowRenderer.getWindow();

	Orbital::Gui::DebugLayer debugLayer;
	debugLayer.initialize(window);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use
	// ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application
	// (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling
	// ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double
	// backslash \\ !
	// io.Fonts->AddFontDefault();
	// io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	// io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	// ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL,
	// io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!window->shouldClose())
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
		// inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or
		// clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
		// clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui, and
		// hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		debugLayer.beginFrame();

		int display_w, display_h;
		glfwGetFramebufferSize((GLFWwindow*)window->getNativeWindow(), &display_w, &display_h);
		//glad_glViewport(0, 0, display_w, display_h);

		Orbital::RenderAPI::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Orbital::RenderAPI::Clear();
		debugLayer.endFrame();

		window->swapBuffers();
	}

	// Cleanup

	lowRenderer.terminate();

	return 0;
}
