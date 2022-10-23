#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
    class OrbitalApplication;

    template<typename T>
    class ServiceInterface
    {
    public:
        std::shared_ptr<T> mInstance = nullptr;
    };
}
