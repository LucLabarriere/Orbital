#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
    class VertexArray;
    class VertexBuffer;

    class OENGINE_API VertexContainer
    {
    public:
        virtual ~VertexContainer();

        VertexArray* getVao();
        inline size_t getVertexCount() const { return mVertexCount; };

        static VertexContainer* Triangle();
        static VertexContainer* Quad();
        static VertexContainer* Cube();
    
    private:
        VertexContainer(VertexArray* vao, VertexBuffer* vbo, size_t vertexCount);

    private:
        VertexArray* mVAO = nullptr;
        VertexBuffer* mVBO = nullptr;
        size_t mVertexCount = 0;
    };
}
