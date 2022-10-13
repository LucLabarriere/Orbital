#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalTools/Maths.h"


namespace Orbital
{
    HighRenderer::HighRenderer()
        : mLowRenderer(), mModel(1.0f)
    {

    }

    HighRenderer::~HighRenderer()
    {
        delete mTriangle;
    }

    void HighRenderer::initialize()
    {
        mLowRenderer.initialize();
        mShader.initialize();
        mShader.mapUniformLocation(Uniform::Model, "u_Model");
        mTriangle = VertexContainer::Triangle();
    }

    void HighRenderer::terminate()
    {
        mLowRenderer.terminate();
    }

    void HighRenderer::drawQuad()
    {
        mShader.bind();
        mShader.setUniform(Uniform::Model, mModel);
        mLowRenderer.render(*mTriangle->getVao(), mTriangle->getVertexCount());
    }
}
