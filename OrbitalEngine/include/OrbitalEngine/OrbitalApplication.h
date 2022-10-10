#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
    class OENGINE_API OrbitalApplication
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
        int run();
        virtual void update() = 0;

    protected:
        Services mServices;

    private:
        HighRenderer mHighRenderer;

    };
}
