#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	RendererInterface::RendererInterface()
		: ServiceInterface()
	{
	}
	RendererInterface::RendererInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void RendererInterface::Initialize()
	{
		mInstance = mApp.lock()->getHighRenderer();
	}

	void RendererInterface::Draw(MeshComponent& mc)
	{
		mInstance->draw(mc);
	}

	MeshComponentHandle RendererInterface::PushMeshComponent(
		Entity& e, const MeshFilterHandle& meshFilter, const TransformHandle& transform
	)
	{
		return mInstance->pushMeshComponent(e, meshFilter, transform);
	}

	Window& RendererInterface::GetWindow()
	{
		return mInstance->getWindow();
	}

	void RendererInterface::OnUpdate()
	{
		mInstance->onUpdate();
	}
} // namespace Orbital
