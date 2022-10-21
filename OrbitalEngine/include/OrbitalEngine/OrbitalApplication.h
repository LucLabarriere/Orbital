#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalTools/Time.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/Scene.h"

namespace Orbital
{
    class OENGINE_API OrbitalApplication
        : public InputManager, private Services::Scene, private Services::Renderer
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
    };
}
