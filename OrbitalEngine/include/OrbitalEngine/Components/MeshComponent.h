#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Components/MeshFilter.h"

namespace Orbital
{
	class HighRenderer;
	class VirtualRenderer;

	class MeshComponent
	{
	public:
		MeshComponent(const MeshFilterHandle& meshFilter, const TransformHandle& transform, std::shared_ptr<VirtualRenderer> renderer)
			: mMeshFilter(meshFilter), mTransform(transform), mRenderer(renderer)
		{
		}

		inline const MeshFilterHandle& getMeshFilter() const
		{
			return mMeshFilter;
		}

		inline const TransformHandle& getTransform()
		{
			return mTransform;
		}

		inline const TransformHandle& getTransform() const
		{
			return mTransform;
		}

		inline const std::shared_ptr<VirtualRenderer>& getRenderer() const { return mRenderer; }

		MeshFilterHandle mMeshFilter;
		TransformHandle mTransform;
		std::shared_ptr<VirtualRenderer> mRenderer;
	};

	using MeshComponentHandle = ComponentHandle<MeshComponent>;
} // namespace Orbital
