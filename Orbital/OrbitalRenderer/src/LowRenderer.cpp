#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Maths.h"

namespace Orbital
{
	LowRenderer::LowRenderer() : mWindow(Window::Create())
	{
	}

	LowRenderer::~LowRenderer()
	{
		LOGFUNC();
	}

	void LowRenderer::initialize(unsigned int windowWidth, unsigned int windowHeight)
	{
		Logger::Trace("Initializing Low renderer");

		RenderAPI::Initialize();
		mWindow->initialize(windowWidth, windowHeight);
		RenderAPI::LateInitialize();

		Logger::Trace("Done initializing Low renderer");
	}

	void LowRenderer::render(const VertexArray& vao, const IndexBuffer& ibo)
	{
		vao.bind();
		ibo.bind();
		RenderAPI::DrawTriangles(0, ibo.getIndexCount());
		mDrawCalls += 1;
	}

	void LowRenderer::terminate()
	{
		RenderAPI::Terminate();
		Logger::Trace("Deleting window...");
		delete mWindow;
		Logger::Trace("Deleted window");
	}
} // namespace Orbital
