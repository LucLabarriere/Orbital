#pragma once

#include "OrbitalEngine/ECS/Components/Component.h"
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

	class MeshComponent : public Component
	{
	public:
		MeshComponent(
			const EntityID& entityID, const WeakRef<ECSManager>& manager, const MeshFilterHandle& meshFilter,
			const TransformHandle& transform, WeakRef<VirtualRenderer> renderer
		)
			: Component(entityID, manager), mMeshFilter(meshFilter), mTransform(transform), mRenderer(renderer)
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

		inline const WeakRef<VirtualRenderer>& getRenderer() const
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
		WeakRef<VirtualRenderer> mRenderer;
		Maths::Vec4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	using MeshComponentHandle = SafeHandle<MeshComponent>;

	template <>
	inline Orbital::SafeHandle<Orbital::MeshComponent> Orbital::Entity::push<Orbital::MeshComponent>()
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

		auto meshRenderer = Renderer.Get().lock()->getRenderer(meshFilter->mesh);
		auto meshComponent = push<MeshComponent>(meshFilter, transform, meshRenderer);

		return meshComponent;
	}
} // namespace Orbital
