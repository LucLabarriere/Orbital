#pragma once

#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalInputs/Event.h"

namespace Orbital
{
    class EditorApplication : public OrbitalApplication
    {
    public:
        EditorApplication();

        virtual void initialize() override;
        virtual void terminate() override;

        virtual void onLoad() override;
        virtual void update(const Time& dt) override;
        virtual bool onKeyPressed(KeyPressedEvent& e) override;

    private:
        void initializeScripts();
    };
}
