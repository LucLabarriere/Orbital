#include "OrbitalEngine/Services/RendererService.h"
#include "OrbitalEngine/HighRenderer.h"

namespace Orbital
{
    RendererService::RendererInterface::RendererInterface(std::shared_ptr<HighRenderer> instance)
        : ServiceInterface<HighRenderer>(instance)
    {

    }

    void RendererService::RendererInterface::Draw(MeshComponent& mc)
    {
        mInstance->draw(mc);
    }

    Window& RendererService::RendererInterface::GetWindow()
    {
        return mInstance->getWindow();
    }

    void RendererService::RendererInterface::Terminate()
    {
        mInstance->terminate();
    }
}
