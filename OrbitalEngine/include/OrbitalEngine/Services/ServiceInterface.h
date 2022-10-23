#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
    class OrbitalApplication;

    template<typename T>
    class ServiceInterface
    {
    public:
        ServiceInterface() : mInstance(nullptr) { }
        ServiceInterface(std::shared_ptr<T> instance) : mInstance(instance) { }

        std::shared_ptr<T> mInstance = nullptr;
    };
}
