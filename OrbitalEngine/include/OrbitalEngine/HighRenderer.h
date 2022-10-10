#pragma once

#include "OrbitalRenderer/LowRenderer.h"

namespace Orbital
{
    class HighRenderer
    {
    public:
        HighRenderer();
        HighRenderer(HighRenderer &&) = delete;
        HighRenderer(const HighRenderer &) = delete;
        HighRenderer &operator=(HighRenderer &&) = delete;
        HighRenderer &operator=(const HighRenderer &) = delete;
        virtual ~HighRenderer();

        void initialize();
    
    private:
        LowRenderer mLowRenderer;
    };
}
