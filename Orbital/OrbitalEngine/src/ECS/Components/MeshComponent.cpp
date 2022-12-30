#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"

namespace Orbital
{
	void MeshComponent::setRenderOrder(size_t position)
	{
		mEngine.lock()->setRenderOrder(mEntityID, position);
	}

	template <>
	OENGINE_API SafeHandle<MeshComponent> Entity::push<MeshComponent>()
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
	OENGINE_API void Entity::remove<MeshComponent>()
	{
		Orbital::Assert(get<MeshComponent>().isValid() == true, "Trying to remove a non existing component");

		auto meshComponent = get<MeshComponent>();
		Renderer.UnregisterMeshComponent(meshComponent->getEntityID());

		return mManager.lock()->getRegistry()->remove<MeshComponent>(mEntityID);
	}
} // namespace Orbital
