#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
#include "OrbitalLogger/Logger.h" 
#include "OrbitalTools/Maths.h"
#include "OrbitalRenderer/RenderAPI.h"

namespace Orbital
{
    LowRenderer::LowRenderer()
        : mWindow(Window::Create())
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
        delete mWindow;
    }
}
