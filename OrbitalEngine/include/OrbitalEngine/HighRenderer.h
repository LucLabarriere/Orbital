#pragma once

#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ShaderProgram.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalTools/Services.h"

namespace Orbital
{
    class VertexContainer;
    namespace Services { class Renderer; }

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
        friend Services::Renderer;

        LowRenderer mLowRenderer;
        ShaderProgram mShader;
        VertexContainer* mTriangle; // TODO make unique_ptr ? Or shared
        VertexContainer* mQuad;
        VertexContainer* mCube;
    };

    namespace Services
    {
        class Renderer : protected UniqueService<HighRenderer>
        {
        public:
            static inline void Draw(MeshComponent& mc) { sPtr->draw(mc); }

        protected: 
            static inline Window& GetWindow() { return sPtr->getWindow(); }
            static inline void Terminate() { sPtr->terminate(); }

            friend Orbital::OrbitalApplication;
        };
    }
}
