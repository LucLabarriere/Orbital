#pragma once

namespace Orbital
{
    template <typename T>
    class Service
    {
    protected:
        static void Initialize(T& service) { sPtr = &service; }
        static inline T& Get() { return *sPtr; }

    protected:
        static inline T* sPtr = nullptr;
    };
}
