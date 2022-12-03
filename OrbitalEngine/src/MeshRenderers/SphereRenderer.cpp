#include "OrbitalEngine/MeshRenderers/SphereRenderer.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalEngine/Components/MeshComponent.h"

namespace Orbital
{
	void SphereRenderer::initialize()
	{
		mShaderProgram.initialize("assets/shaders/Base.vs.glsl", "assets/shaders/Sphere.fs.glsl");
		mShaderProgram.mapUniformLocation(Uniform::Model, "u_Model");
		mShaderProgram.mapUniformLocation(Uniform::Color, "u_Color");
		mVertexContainer = VertexContainer::Quad();
	}

	void SphereRenderer::terminate()
	{
		VirtualRenderer::terminate();
		mShaderProgram.terminate();
	}

	void SphereRenderer::readyRender(const MeshComponent& mc) const
	{
		mShaderProgram.bind();

		auto model = mc.getTransform()->getModelMatrix();

		mShaderProgram.setUniform<Maths::Vec4>(Uniform::Color, mc.getColor());
		mShaderProgram.setUniform<Maths::Mat4>(Uniform::Model, model);
	}
}
