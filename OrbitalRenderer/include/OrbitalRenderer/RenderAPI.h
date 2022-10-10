#pragma once

namespace Orbital
{
    class RenderAPI
    {
    public:
        static bool Initialize();
        static bool LateInitialize();
        static void Terminate();

        static void Clear();
        static void ClearColor(float r, float g, float b, float a);
        static void PoolEvents();
    };
}
