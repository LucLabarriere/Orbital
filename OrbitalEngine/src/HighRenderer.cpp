#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    HighRenderer::HighRenderer()
        : mLowRenderer()
    {

    }

    HighRenderer::~HighRenderer()
    {
        LOGFUNC();
    }

    void HighRenderer::initialize()
    {
        mLowRenderer.initialize();
        mShader.initialize();
        mShader.mapUniformLocation(Uniform::Model, "u_Model");
        mTriangle = VertexContainer::Triangle();
        mQuad = VertexContainer::Quad();
        mCube = VertexContainer::Cube();
    }

    void HighRenderer::terminate()
    {
        delete mTriangle;
        delete mQuad;
        delete mCube;

        mShader.terminate();
        mLowRenderer.terminate();
    }

    void HighRenderer::draw(MeshComponent& mc) const
    {
        MeshType meshType = mc.getMeshType();
        ComponentHandle<TransformComponent>& transform = mc.getTransform();

        mShader.bind();
        Maths::Mat4 model(1.0f);
        model = Maths::Translate(model, transform->position);
        model = Maths::Rotate(model, transform->rotation.x, { 1.0f, 0.0f, 0.0f });
        model = Maths::Rotate(model, transform->rotation.y, { 0.0f, 1.0f, 0.0f });
        model = Maths::Rotate(model, transform->rotation.z, { 0.0f, 0.0f, 1.0f });
        model = Maths::Scale(model, transform->scale);

        mShader.setUniform<Maths::Mat4>(Uniform::Model, model);

        VertexContainer* container = nullptr;

        switch(mc.getMeshType())
        {
            case MeshType::Triangle:
            {
                container = mTriangle;
                break;
            }
            case MeshType::Quad:
            {
                container = mQuad;
                break;
            }
            case MeshType::Cube:
            {
                container = mCube;
                break;
            }
        }

        mLowRenderer.render(*container->getVao(), *container->getIbo());
    }
}
