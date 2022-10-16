#pragma once

#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
    class EditorApplication : public OrbitalApplication
    {
    public:
        EditorApplication();

        virtual void initialize() override;
        virtual void terminate() override;

        virtual void update(Time dt) override;

    private:
        //void* mScriptsLibrary;
    };
}
