#pragma once

#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalEngine/Context.h"

namespace Orbital
{
    class OENGINE_API HighRenderer
    {
    public:
        HighRenderer();
        HighRenderer(HighRenderer &&) = delete;
        HighRenderer(const HighRenderer &) = delete;
        HighRenderer &operator=(HighRenderer &&) = delete;
        HighRenderer &operator=(const HighRenderer &) = delete;
        virtual ~HighRenderer();

        void initialize();
        void terminate();
        void drawQuad();

    
        Window& getWindow() { return mLowRenderer.getWindow(); }

    private:
        LowRenderer mLowRenderer;
    };
}
