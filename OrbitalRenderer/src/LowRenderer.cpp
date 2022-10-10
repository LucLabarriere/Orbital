#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    LowRenderer::LowRenderer()
        : mWindow(Window::Create())
    {

    }

    LowRenderer::~LowRenderer()
    {

    }

    void LowRenderer::initialize()
    {
        RenderAPI::Initialize();
        mWindow->initialize();
    }

    void LowRenderer::terminate()
    {
        RenderAPI::Terminate();
        delete mWindow;
    }
}
