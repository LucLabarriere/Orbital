#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"
#include "OrbitalEngine/Graphics/VertexContainer.h"

namespace Orbital
{
	VirtualRenderer::VirtualRenderer()
	{
	}

	VirtualRenderer::~VirtualRenderer()
	{
	}

	void VirtualRenderer::terminate()
	{
		delete mVertexContainer;
	};

	void VirtualRenderer::checkShaderChanged()
	{
		auto vsPath = mShaderProgram.getVsPath();
		auto fsPath = mShaderProgram.getFsPath();

		size_t shaderTimeCountVS = mShaderProgram.getCreatedTimeCountVS();
		size_t shaderTimeCountFS = mShaderProgram.getCreatedTimeCountFS();

		size_t newTimeCountVS = Files::Timestamp(vsPath);
		size_t newTimeCountFS = Files::Timestamp(fsPath);

		if (shaderTimeCountVS != newTimeCountVS or shaderTimeCountFS != newTimeCountFS)
		{
			Logger::Debug(shaderTimeCountVS, " ", newTimeCountVS);
			Logger::Log("Shader changed, recompiling...");
			mShaderProgram = ShaderProgram();
			initialize();
		}
	}

	auto VirtualRenderer::getVao() const -> VertexArray*
	{
		return mVertexContainer->getVao();
	}

	auto VirtualRenderer::getIbo() const -> IndexBuffer*
	{
		return mVertexContainer->getIbo();
	}
} // namespace Orbital
