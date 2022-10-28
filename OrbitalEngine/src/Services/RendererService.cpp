#include "OrbitalEngine/Services/RendererService.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	RendererInterface::RendererInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void RendererInterface::Initialize()
	{
		mInstance = mApp->getHighRenderer();
	}

	void RendererInterface::Draw(MeshComponent& mc)
	{
		mInstance->draw(mc);
	}

	MeshComponentHandle RendererInterface::PushMeshComponent(
		Entity& e, MeshType meshType, const TransformHandle& transform
	)
	{
		return mInstance->pushMeshComponent(e, meshType, transform);
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
