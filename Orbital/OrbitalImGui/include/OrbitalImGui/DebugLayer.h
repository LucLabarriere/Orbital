#pragma once

namespace Orbital
{
	class Window;

	namespace Gui
	{
		class DebugLayer
		{
		public:
			DebugLayer();
			~DebugLayer(){};

			void initialize(Window* window);
			void beginFrame();
			void endFrame();
			void terminate();

		private:
			void showStatistics();

		private:
			bool mShowDemoWindow = true;
		};
	} // namespace ImGui
} // namespace Orbital
