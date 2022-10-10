#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    OrbitalApplication::OrbitalApplication()
        : mHighRenderer()
    {

    }

    OrbitalApplication::~OrbitalApplication()
    {

    }

    void OrbitalApplication::initialize()
    {
        Logger::Log("Initializing application");
        mHighRenderer.initialize();
    }

    void OrbitalApplication::terminate()
    {
        Logger::Log("Terminating application");
    }

    int OrbitalApplication::run()
    {
        initialize();
        terminate();
        return 0;
    }
}
