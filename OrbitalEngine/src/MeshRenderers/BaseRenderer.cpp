#include "OrbitalEngine/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/VertexContainer.h" 

namespace Orbital
{
	void BaseRenderer::initialize()
	{
		mShaderProgram.initialize("assets/shaders/Base.vs.glsl", "assets/shaders/Base.fs.glsl");
		mShaderProgram.mapUniformLocation(Uniform::Model, "u_Model");
		mVertexContainer = VertexContainer::Quad();
	}

	void BaseRenderer::terminate()
	{
		VirtualRenderer::terminate();
		mShaderProgram.terminate();
	}

	void BaseRenderer::readyRender(const MeshComponent& mc) const
	{
		mShaderProgram.bind();

		auto& meshFilter = mc.getMeshFilter();
		auto& transform = mc.getTransform();
		Maths::Mat4 model = transform->getModelMatrix();

		mShaderProgram.setUniform<Maths::Mat4>(Uniform::Model, model);
	}
} // namespace Orbital
