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

	void LowRenderer::initialize()
	{
		Logger::Trace("Initializing Low renderer");

		RenderAPI::Initialize();
		mWindow->initialize();
		RenderAPI::LateInitialize();

		Logger::Trace("Done initializing Low renderer");
	}

	void LowRenderer::render(const VertexArray& vao, const IndexBuffer& ibo) const
	{
		vao.bind();
		ibo.bind();
		RenderAPI::DrawTriangles(0, ibo.getIndexCount());
	}

	void LowRenderer::terminate()
	{
		RenderAPI::Terminate();
		Logger::Trace("Deleting window...");
		delete mWindow;
		Logger::Trace("Deleted window");
	}
} // namespace Orbital
