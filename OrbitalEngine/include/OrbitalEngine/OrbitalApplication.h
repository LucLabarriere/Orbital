#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalInputs/InputManager.h"

namespace Orbital
{
    class OENGINE_API OrbitalApplication : public InputManager
    {
    public:
        OrbitalApplication();
        OrbitalApplication(OrbitalApplication &&) = delete;
        OrbitalApplication(const OrbitalApplication &) = delete;
        OrbitalApplication &operator=(OrbitalApplication &&) = delete;
        OrbitalApplication &operator=(const OrbitalApplication &) = delete;
        virtual ~OrbitalApplication();

        void initialize(); 
        void terminate();

        virtual bool onKeyPressed(KeyPressedEvent& e) override;
        virtual bool onMouseMove(MouseMoveEvent& e) override;

        int run();
        virtual void update() = 0;

    protected:
        Services mServices;

    private:
        HighRenderer mHighRenderer;

    };
}
