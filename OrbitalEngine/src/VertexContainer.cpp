#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalRenderer/VertexArray.h"
#include "OrbitalRenderer/VertexBuffer.h"

namespace Orbital
{
    VertexContainer::VertexContainer(VertexArray* vao, VertexBuffer* vbo, size_t vertexCount)
        : mVAO(vao), mVBO(vbo), mVertexCount(vertexCount)
    {

    }

    VertexContainer::~VertexContainer()
    {
        delete mVAO;
        delete mVBO;
    }

    VertexArray* VertexContainer::getVao()
    {
        return mVAO;
    }

    VertexContainer* VertexContainer::Triangle()
    {
        float vertices[18] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        auto vao = VertexArray::Create();
        vao->bind();
        auto vbo = VertexBuffer::Create(sizeof(float) * 18, sizeof(float) * 6, &vertices[0]);
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

        return new VertexContainer(vao, vbo, 3);
    }

    VertexContainer* VertexContainer::Quad() // TODO Change here
    {
        float vertices[18] = {
             0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        auto vao = VertexArray::Create();
        vao->bind();
        auto vbo = VertexBuffer::Create(sizeof(float) * 18, sizeof(float) * 6, &vertices[0]);
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

        return new VertexContainer(vao, vbo, 3);
    }

    VertexContainer* VertexContainer::Cube() // TODO Change here
    {
        float vertices[18] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        auto vao = VertexArray::Create();
        vao->bind();
        auto vbo = VertexBuffer::Create(sizeof(float) * 18, sizeof(float) * 6, &vertices[0]);
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
        vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

        return new VertexContainer(vao, vbo, 3);
    }
}
