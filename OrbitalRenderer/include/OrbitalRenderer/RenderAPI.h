#pragma once

#include "OrbitalRenderer/Context.h"

namespace Orbital
{
    using EventCallbackFunction = std::function<void(const std::string& message)>;

    class ORENDERER_API RenderAPI
    {
    public:
        static bool Initialize();
        static bool LateInitialize();
        static void Terminate();

        static void SetEventCallback(EventCallbackFunction callback)
        {
            sEventCallback = callback;
        }
        static void EventCallback(const std::string& message)
        {
            sEventCallback(message);
        }
        static void DrawTriangles(size_t firstIndex, size_t vertexCount);
        static void Clear();
        static void ClearColor(float r, float g, float b, float a);
        static void PoolEvents();

    protected:
        static inline EventCallbackFunction sEventCallback;
    };
}
