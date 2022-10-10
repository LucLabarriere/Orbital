#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
namespace Orbital
{
    LowRenderer::LowRenderer()
        : mWindow(Window::Create())
    {

    }

    LowRenderer::~LowRenderer()
    {

    }

    void LowRenderer::initialize()
    {
        RenderAPI::Initialize();
        mWindow->initialize();
        RenderAPI::LateInitialize();

        glad_glGenVertexArrays(1, &vao);
        glad_glBindVertexArray(vao);
          
        glad_glGenBuffers(1, &vbo);
        glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glad_glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);
          
        glad_glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
          
        glad_glEnableVertexAttribArray(0);
        glad_glBindVertexArray(0);
    }

    void LowRenderer::render(unsigned int vao2, unsigned int vbo)
    {
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
         *
         *
         *
         * For the first tests:
         * Make a very simple Mesh that is a triangle
         *
         * */

    }

    void LowRenderer::terminate()
    {
        RenderAPI::Terminate();
        delete mWindow;
    }
}
