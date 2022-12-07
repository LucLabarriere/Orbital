#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Graphics/ShaderProgram.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	class MeshComponent;
	class VertexArray;
	class IndexBuffer;
	class VertexContainer;

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

		VertexArray* getVao() const;
		IndexBuffer* getIbo() const;

	protected:
		ShaderProgram mShaderProgram; // Should be a pointer to an instance in a ShaderLibrary
		VertexContainer* mVertexContainer = nullptr; // Should be a smart pointer
	};
} // namespace Orbital
