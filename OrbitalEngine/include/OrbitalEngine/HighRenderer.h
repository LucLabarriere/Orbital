#pragma once

#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ShaderProgram.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"

namespace Orbital
{
    class VertexContainer;

    class OENGINE_API HighRenderer
    {
    public:
        HighRenderer();
        HighRenderer(HighRenderer &&) = delete;
        HighRenderer(const HighRenderer &) = delete;
        HighRenderer &operator=(HighRenderer &&) = delete;
        HighRenderer &operator=(const HighRenderer &) = delete;
        virtual ~HighRenderer();

        void initialize();
        void terminate();
        void draw(MeshComponent& mc) const;

        Window& getWindow() { return mLowRenderer.getWindow(); }

    private:
        LowRenderer mLowRenderer;
        ShaderProgram mShader;
        VertexContainer* mTriangle;
        VertexContainer* mQuad;
        VertexContainer* mCube;
    };
}
