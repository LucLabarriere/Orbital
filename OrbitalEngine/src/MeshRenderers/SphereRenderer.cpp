#include "OrbitalEngine/MeshRenderers/SphereRenderer.h"
#include "OrbitalTools/Files.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalEngine/Components/MeshComponent.h"

namespace Orbital
{
	void SphereRenderer::initialize()
	{
		mShaderProgram.initialize("assets/shaders/Base.vs.glsl", "assets/shaders/Sphere.fs.glsl");
		mShaderProgram.mapUniformLocation(Uniform::Model, "u_Model");
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

		auto transform = mc.getTransform();

		Maths::Mat4 model(1.0f);
		model = Maths::Translate(model, transform->position);
		model = Maths::Scale(model, transform->scale);

		mShaderProgram.setUniform<Maths::Mat4>(Uniform::Model, model);
	}
}
