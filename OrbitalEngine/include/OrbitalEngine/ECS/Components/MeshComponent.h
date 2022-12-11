#pragma once

#include "OrbitalEngine/ECS/Components/MeshFilter.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"

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
			std::weak_ptr<VirtualRenderer> renderer
		)
			: mMeshFilter(meshFilter), mTransform(transform), mRenderer(renderer)
		{
		}

		inline const MeshFilterHandle& getMeshFilter() const
		{
			return mMeshFilter;
		}

		inline TransformHandle& getTransform()
		{
			return mTransform;
		}

		inline const TransformHandle& getTransform() const
		{
			return mTransform;
		}

		inline const std::weak_ptr<VirtualRenderer>& getRenderer() const
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
		std::weak_ptr<VirtualRenderer> mRenderer;
		Maths::Vec4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	using MeshComponentHandle = SafeHandle<MeshComponent>;

	template <>
	inline Orbital::SafeHandle<Orbital::MeshComponent> Orbital::Entity::push<
		Orbital::MeshComponent, std::weak_ptr<Orbital::HighRenderer>>(
		const std::weak_ptr<Orbital::HighRenderer> renderer
	)
	{
		SafeHandle<MeshFilter> meshFilter = get<MeshFilter>();

		if (!meshFilter.isValid())
		{
			meshFilter = push<MeshFilter>(MeshType::Quad);
		}

		SafeHandle<TransformComponent> transform = get<TransformComponent>();

		if (!transform.isValid())
		{
			transform = push<TransformComponent>();
		}

		auto meshRenderer = renderer.lock()->getRenderer(meshFilter->mesh);
		auto meshComponent = push<MeshComponent>(meshFilter, transform, meshRenderer);

		return meshComponent;
	}
} // namespace Orbital
