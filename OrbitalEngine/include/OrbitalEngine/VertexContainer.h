#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
    class VertexArray;
    class IndexBuffer;
    class VertexBuffer;

    class OENGINE_API VertexContainer
    {
    public:
        virtual ~VertexContainer();

        VertexArray* getVao();
        IndexBuffer* getIbo();
        inline size_t getVertexCount() const { return mVertexCount; };

        static VertexContainer* Triangle();
        static VertexContainer* Quad();
        static VertexContainer* Cube();
    
    private:
        VertexContainer(VertexArray* vao, IndexBuffer* ibo, VertexBuffer* vbo, size_t vertexCount);

    private:
        VertexArray* mVAO = nullptr;
        IndexBuffer* mIBO = nullptr;
        VertexBuffer* mVBO = nullptr;
        size_t mVertexCount = 0;
    };
}
