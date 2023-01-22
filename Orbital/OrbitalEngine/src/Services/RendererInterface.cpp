#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	RendererInterface::RendererInterface() : ServiceInterface()
	{
	}
	RendererInterface::RendererInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void RendererInterface::InitializeInterface()
	{
		mInstance = mApp.lock()->getHighRenderer();
	}

	void RendererInterface::Draw(MeshComponent& mc)
	{
		mInstance.lock()->draw(mc);
	}

	void RendererInterface::BindCamera()
	{
		mInstance.lock()->bindCamera();
	}

	void RendererInterface::RegisterMeshComponent(const MeshComponentHandle& meshComponent)
	{
		mInstance.lock()->registerMeshComponent(meshComponent);
	}

	void RendererInterface::UnregisterMeshComponent(const EntityID& id)
	{
		mInstance.lock()->unregisterMeshComponent(id);
	}

	void RendererInterface::ClearComponents()
	{
		mInstance.lock()->clearComponents();
	}

	void RendererInterface::SetCamera(const CameraHandle& camera)
	{
		mInstance.lock()->setCamera(camera);
	}

	void RendererInterface::OnUpdate()
	{
		mInstance.lock()->onUpdate();
	}
} // namespace Orbital
