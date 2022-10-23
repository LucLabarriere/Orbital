#pragma once

#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
    class OrbitalApplication;
    class HighRenderer;

    struct RendererService
    {
    public:
        class RendererInterface : public ServiceInterface<HighRenderer>
        {
        public:
            RendererInterface(std::shared_ptr<HighRenderer> instance);

            void Draw(MeshComponent& mc);
            Window& GetWindow();

        protected:
            friend Orbital::OrbitalApplication;

            void Terminate();
        } Renderer = RendererInterface(nullptr);
    };
}
