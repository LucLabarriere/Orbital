#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ShaderProgram.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	class MeshComponent;

	enum class MeshRendererType
	{
		Base = 0,
		Sphere
	};

	class VirtualRenderer
	{
	public:
		VirtualRenderer()
		{
		}

		virtual ~VirtualRenderer()
		{
		}

		virtual void initialize() = 0;
		virtual void terminate() { delete mVertexContainer; };
		virtual void readyRender(const MeshComponent& mc) const = 0;

		void checkShaderChanged()
		{
			auto vsPath = mShaderProgram.getVsPath();
			auto fsPath = mShaderProgram.getFsPath();

			size_t shaderTimeCountVS = mShaderProgram.getCreatedTimeCountVS();
			size_t shaderTimeCountFS = mShaderProgram.getCreatedTimeCountFS();

			size_t newTimeCountVS = Files::GetFileModifiedTime(vsPath);
			size_t newTimeCountFS = Files::GetFileModifiedTime(fsPath);

			if (shaderTimeCountVS != newTimeCountVS or shaderTimeCountFS != newTimeCountFS)
			{
				Logger::Debug(shaderTimeCountVS, " ", newTimeCountVS);
				Logger::Log("Shader changed, recompiling...");
				mShaderProgram = ShaderProgram();
				initialize();
			}
		}

		inline VertexArray* getVao() const { return mVertexContainer->getVao(); }
		inline IndexBuffer* getIbo() const { return mVertexContainer->getIbo(); }

	protected:
		ShaderProgram mShaderProgram; // Should be a pointer to an instance in a ShaderLibrary
		VertexContainer* mVertexContainer = nullptr;
	};
} // namespace Orbital
