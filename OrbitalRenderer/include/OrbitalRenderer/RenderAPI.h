#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    class ORENDERER_API RenderAPI
    {
    public:
        static bool Initialize();
        static bool LateInitialize();
        static void Terminate();

        static void DrawTriangles(size_t firstIndex, size_t vertexCount);
        static void Clear();
        static void ClearColor(float r, float g, float b, float a);
        static void PoolEvents();
    };
}
