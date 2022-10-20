#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalTools/Time.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

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

        virtual void initialize(); 
        virtual void terminate();

        int run(int argc, char** argv);
        virtual void update(Time dt) = 0;

    protected:
        HighRenderer mHighRenderer;
        Window* mWindow;
        Registry mRegistry;
        ScriptsLibraryLoader mScriptsLibrary;
    };
}
