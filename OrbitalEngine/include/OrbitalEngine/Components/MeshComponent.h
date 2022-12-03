#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Components/MeshFilter.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class HighRenderer;
	class VirtualRenderer;

	class MeshComponent // TODO, rename RenderComponent ?
	{
	public:
		MeshComponent(
			const MeshFilterHandle& meshFilter, const TransformHandle& transform,
			std::shared_ptr<VirtualRenderer> renderer
		)
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

		inline const std::shared_ptr<VirtualRenderer>& getRenderer() const
		{
			return mRenderer;
		}

		inline void setColor(const Maths::Vec4& color)
		{
			mColor = color;
		}

		inline const Maths::Vec4& getColor() const
		{
			return mColor;
		}

		MeshFilterHandle mMeshFilter;
		TransformHandle mTransform;
		std::shared_ptr<VirtualRenderer> mRenderer;
		Maths::Vec4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	using MeshComponentHandle = ComponentHandle<MeshComponent>;
} // namespace Orbital
