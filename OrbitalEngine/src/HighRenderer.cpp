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
}
