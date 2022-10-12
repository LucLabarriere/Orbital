#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
#include "OrbitalLogger/Logger.h" 

namespace Orbital
{
    LowRenderer::LowRenderer()
        : mWindow(Window::Create())
    {

    }

    LowRenderer::~LowRenderer()
    {
        delete mVAO;
        delete mVAO2;
        delete mVBO;
        delete mVBO2;
        delete mShader;
    }

    void LowRenderer::initialize()
    {
        RenderAPI::Initialize();
        mWindow->initialize();
        RenderAPI::LateInitialize();

        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aCol;\n"
            "out vec4 v_Color;"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "   v_Color = vec4(aCol, 1.0);\n"
        "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
            "in vec4 v_Color;\n"
            "out vec4 o_Color;\n"
            "void main()\n"
            "{\n"
            "o_Color = v_Color;"
        "}\0";

        mShader = Shader::Create(vertexShaderSource, fragmentShaderSource);
        mShader->bind();

        mVAO = VertexArray::Create();
        mVAO->bind();

        mVBO = VertexBuffer::Create(sizeof(vertices), 6 * sizeof(float), vertices);
        mVBO->addVertexAttribute(3, sizeof(float) * 3);
        mVBO->addVertexAttribute(3, sizeof(float) * 3);

        mVAO2 = VertexArray::Create();
        mVAO2->bind();

        mVBO2 = VertexBuffer::Create(sizeof(vertices2), 6 * sizeof(float), vertices2);
        mVBO2->addVertexAttribute(3, sizeof(float) * 3);
        mVBO2->addVertexAttribute(3, sizeof(float) * 3);
    }

    void LowRenderer::render(unsigned int vao2, unsigned int vbo)
    {
        mVAO->bind();
        RenderAPI::DrawTriangles(0, 3);
        mVAO2->bind();
        RenderAPI::DrawTriangles(0, 3);

        /* TODO
         * Implement simple shader to display things temporarily
         *
         * Implement VertexBuffer, VertexArray, IndexBuffer (OrbitalRenderer)
         * Implement Shader
         *
         * Example of usage from the highRenderer:
         * highRenderer->draw(meshRenderer);
         *
         * struct MeshComponent 
         * {
         *  Transform& transform;
         *  Mesh& mesh,
         * };
         *
         * The "Mesh" definition here is the high level Mesh
         * It should be contained in a MeshManager
         * that is unordered_map<MeshName, Mesh> mMeshes
         *
         * and should consist of:
         * class Mesh
         * {
         *
         * const void* getVertexData() { return mVertices.getData(); }
         * const void* getIndexData() { return mIndices.getData(); }
         * 
         * private:
         * VertexContainer mVertices;
         * IndexContainer mIndices;
         * }
         *
         * In the LowRenderer, another mesh is defined: "MeshRepresentation"
         *
         * class MeshRepresentation
         * {
         * private:
         * VertexArray vao;
         * VertexBuffer vbo;
         * IndexBuffer ibo;
         * }
         * 
         * So that the usage is the following:
         *
         * // In Application:
         * MeshComponent mc = { Transform(), mServices.meshManager->get("Triangle")}; // Later in the ECS
         * mServices.renderer->requestDraw(mc)
         *
         * // In the HighRenderer
         * void requestDraw(MeshComponent& mc)
         * {
         *      
         * }
         *
         * For the first tests:
         * Make a very simple Mesh that is a triangle
         * */

    }

    void LowRenderer::terminate()
    {
        RenderAPI::Terminate();
        delete mWindow;
    }
}
