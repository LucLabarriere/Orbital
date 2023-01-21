#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"

namespace Orbital
{
	MeshComponent::MeshComponent(const Component::InitArgs& c, const MeshComponent::InitArgs& args)
		: Component(c), mMeshFilter(args.meshFilter), mTransform(args.transform), mEngine(args.engine),
		  mRenderer(args.renderer)
	{
	}

	auto MeshComponent::getMeshFilter() const -> const MeshFilterHandle&
	{
		return mMeshFilter;
	}

	auto MeshComponent::getTransform() -> TransformHandle&
	{
		return mTransform;
	}

	auto MeshComponent::getTransform() const -> const TransformHandle&
	{
		return mTransform;
	}

	auto MeshComponent::getRenderer() const -> const WeakRef<VirtualRenderer>&
	{
		return mRenderer;
	}

	auto MeshComponent::getColor() const -> const Maths::Vec4&
	{
		return mColor;
	}

	auto MeshComponent::setColor(const Maths::Vec4& color) -> void
	{
		mColor = color;
	}

	auto MeshComponent::setRenderOrder(size_t position) -> void
	{
		mEngine.lock()->setRenderOrder(mEntityID, position);
	}

	template <>
	auto Entity::push<MeshComponent>() -> SafeHandle<MeshComponent>
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
		auto meshComponent = push<MeshComponent>(MeshComponent::InitArgs{
			.engine = Renderer.Get(), .meshFilter = meshFilter, .transform = transform, .renderer = meshRenderer });
		Renderer.RegisterMeshComponent(meshComponent);

		return meshComponent;
	}

	template <>
	auto Entity::remove<MeshComponent>() -> void
	{
		Orbital::Assert(get<MeshComponent>().isValid() == true, "Trying to remove a non existing component");

		auto meshComponent = get<MeshComponent>();
		Renderer.UnregisterMeshComponent(meshComponent->getEntityID());

		return mManager.lock()->getRegistry()->remove<MeshComponent>(mEntityID);
	}

} // namespace Orbital
