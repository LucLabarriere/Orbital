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

		MeshComponent(const Component::InitArgs& c, const MeshComponent::InitArgs& args);

		[[nodiscard]] auto getMeshFilter() const -> const MeshFilterHandle&;
		[[nodiscard]] auto getTransform() -> TransformHandle&;
		[[nodiscard]] auto getTransform() const -> const TransformHandle&;
		[[nodiscard]] auto getRenderer() const -> const WeakRef<VirtualRenderer>&;
		[[nodiscard]] auto getColor() const -> const Maths::Vec4&;

		auto setColor(const Maths::Vec4& color) -> void;
		auto setRenderOrder(size_t position) -> void;

		MeshFilterHandle mMeshFilter;
		TransformHandle mTransform;
		WeakRef<HighRenderer> mEngine;
		WeakRef<VirtualRenderer> mRenderer;
		Maths::Vec4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	using MeshComponentHandle = SafeHandle<MeshComponent>;

	template <>
	ORBITAL_ENGINE_API auto Entity::push<MeshComponent>() -> SafeHandle<MeshComponent>;

	template <>
	ORBITAL_ENGINE_API auto Entity::remove<MeshComponent>() -> void;
} // namespace Orbital
