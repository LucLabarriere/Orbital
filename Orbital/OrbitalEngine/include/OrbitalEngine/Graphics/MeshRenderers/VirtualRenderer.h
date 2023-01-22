#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Graphics/ShaderProgram.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	enum class MeshRendererType
	{
		Base = 0,
		Sphere
	};

	class VirtualRenderer
	{
	public:
		VirtualRenderer();
		virtual ~VirtualRenderer();

		virtual void initialize() = 0;
		virtual void terminate();
		virtual void readyRender(const MeshComponent& mc) const = 0;
		void checkShaderChanged();

		auto getVao() const -> VertexArray*;
		auto getIbo() const -> IndexBuffer*;
		auto getShaderProgram() const -> const ShaderProgram& { return mShaderProgram; }

	protected:
		ShaderProgram
			mShaderProgram; // Should be a pointer to an instance in a ShaderLibrary
		VertexContainer* mVertexContainer = nullptr; // Should be a smart pointer
	};
} // namespace Orbital
