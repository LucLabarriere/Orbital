#pragma once

namespace Orbital
{
    class RenderAPI
    {
    public:
        static void Initialize();
        static void Terminate();

        static void Clear();
        static void ClearColor(float r, float g, float b, float a);
        static void PoolEvents();
    };
}
