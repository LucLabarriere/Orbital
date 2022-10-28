#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Components/TransformComponent.h"

namespace Orbital
{
	class HighRenderer;
	class VirtualRenderer;

	enum class MeshType
	{
		Triangle = 0,
		Quad,
		Cube,
		Sphere
	};

	class MeshComponent
	{
	public:
		MeshComponent(MeshType meshType, const TransformHandle& transform, std::shared_ptr<VirtualRenderer> renderer)
			: mMeshType(meshType), mTransform(transform), mRenderer(renderer)
		{
		}

		inline MeshType getMeshType() const
		{
			return mMeshType;
		}

		inline ComponentHandle<TransformComponent>& getTransform()
		{
			return mTransform;
		}

		inline const ComponentHandle<TransformComponent>& getTransform() const
		{
			return mTransform;
		}

		inline const std::shared_ptr<VirtualRenderer>& getRenderer() const { return mRenderer; }

		MeshType mMeshType;
		TransformHandle mTransform;
		std::shared_ptr<VirtualRenderer> mRenderer;
	};

	using MeshComponentHandle = ComponentHandle<MeshComponent>;
} // namespace Orbital
