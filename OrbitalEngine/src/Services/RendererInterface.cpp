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
		mInstance.lock()->draw(mc);
	}

	Window& RendererInterface::GetWindow()
	{
		return mInstance.lock()->getWindow();
	}

	void RendererInterface::OnUpdate()
	{
		mInstance.lock()->onUpdate();
	}
} // namespace Orbital
