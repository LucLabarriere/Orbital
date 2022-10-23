#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalInputs/Core.h"

#include "OrbitalEngine/Services/ServiceManager.h"

namespace Orbital
{
    class Window;

    class OENGINE_API OrbitalApplication
        : public InputManager
    {
    public:
        OrbitalApplication();
        OrbitalApplication(OrbitalApplication &&) = delete;
        OrbitalApplication(const OrbitalApplication &) = delete;
        OrbitalApplication &operator=(OrbitalApplication &&) = delete;
        OrbitalApplication &operator=(const OrbitalApplication &) = delete;
        virtual ~OrbitalApplication();

        virtual void initialize(); 
        virtual void terminate();

        int run(int argc, char** argv);

        virtual void onLoad() { };
        virtual void update(const Time& dt);

    protected:
        Window* mWindow;

        CompleteServiceManager mServices;
    };
}
