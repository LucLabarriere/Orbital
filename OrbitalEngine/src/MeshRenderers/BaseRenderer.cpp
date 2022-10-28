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

		MeshType meshType = mc.getMeshType();
		auto transform = mc.getTransform();

		Maths::Mat4 model(1.0f);
		model = Maths::Translate(model, transform->position);
		model = Maths::Rotate(model, transform->rotation.x, { 1.0f, 0.0f, 0.0f });
		model = Maths::Rotate(model, transform->rotation.y, { 0.0f, 1.0f, 0.0f });
		model = Maths::Rotate(model, transform->rotation.z, { 0.0f, 0.0f, 1.0f });
		model = Maths::Scale(model, transform->scale);

		mShaderProgram.setUniform<Maths::Mat4>(Uniform::Model, model);
	}
} // namespace Orbital
