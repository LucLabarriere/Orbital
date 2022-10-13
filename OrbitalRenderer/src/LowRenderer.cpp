#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
#include "OrbitalLogger/Logger.h" 
#include "OrbitalTools/Maths.h"
#include "OrbitalRenderer/RenderAPI.h"

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

    }

    void LowRenderer::render(const VertexArray& vao, size_t vertexCount)
    {
        vao.bind();
        RenderAPI::DrawTriangles(0, vertexCount);

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
