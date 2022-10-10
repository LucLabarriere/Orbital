#include "OrbitalEngine/HighRenderer.h"

namespace Orbital
{
    HighRenderer::HighRenderer()
        : mLowRenderer()
    {

    }

    HighRenderer::~HighRenderer()
    {

    }

    void HighRenderer::initialize()
    {
        mLowRenderer.initialize();
    }

    void HighRenderer::terminate()
    {
        mLowRenderer.terminate();
    }

    void HighRenderer::drawQuad()
    {
        mLowRenderer.render(0, 0);
    }
}
