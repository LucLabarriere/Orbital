#include "OrbitalEngine/Graphics/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Graphics/VertexContainer.h" 
#include "OrbitalEngine/ECS/Components/MeshComponent.h"

namespace Orbital
{
	void BaseRenderer::initialize()
	{
		mShaderProgram.initialize("assets/shaders/Base.vs.glsl", "assets/shaders/Base.fs.glsl");
		mShaderProgram.mapUniformLocation(Uniform::Model, "u_Model");
		mShaderProgram.mapUniformLocation(Uniform::View, "u_View");
		mShaderProgram.mapUniformLocation(Uniform::Color, "u_Color");
		mVertexContainer = VertexContainer::Cube();
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
		model[3][0] = - model[3][0]; // Reversing x coordinate

		mShaderProgram.setUniform<Maths::Vec4>(Uniform::Color, mc.getColor());
		mShaderProgram.setUniform<Maths::Mat4>(Uniform::Model, model);
	}
} // namespace Orbital
