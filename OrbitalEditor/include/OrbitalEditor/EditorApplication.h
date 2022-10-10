#pragma once

#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
    class EditorApplication : public OrbitalApplication
    {
    public:
        EditorApplication();

        virtual void update() override;

    private:
    };
}
