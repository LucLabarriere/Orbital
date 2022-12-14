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
		struct InitArgs
		{
			const WeakRef<HighRenderer>& engine;
			const MeshFilterHandle& meshFilter;
			const TransformHandle& transform;
			const WeakRef<VirtualRenderer> renderer;
		};

		MeshComponent(const Component::InitArgs& c, const MeshComponent::InitArgs& args)
			: Component(c), mEngine(args.engine), mMeshFilter(args.meshFilter),
			  mTransform(args.transform), mRenderer(args.renderer)
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

		void setRenderOrder(size_t position);

		MeshFilterHandle mMeshFilter;
		TransformHandle mTransform;
		WeakRef<HighRenderer> mEngine;
		WeakRef<VirtualRenderer> mRenderer;
		Maths::Vec4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	using MeshComponentHandle = SafeHandle<MeshComponent>;

	template <>
	OENGINE_API SafeHandle<MeshComponent> Entity::push<MeshComponent>();

	template <>
	OENGINE_API void Entity::remove<MeshComponent>();
} // namespace Orbital
