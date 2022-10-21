#pragma once

#include <memory>
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    class OrbitalApplication;

    namespace Services
    {
        template <typename T>
        class UniqueService 
        {
        private:
            friend Orbital::OrbitalApplication;

            template <typename ...Args>
            static void Initialize(T* instance) { LOGFUNC(); sPtr = std::unique_ptr<T>(instance); }

        protected:
            static inline std::unique_ptr<T> sPtr = nullptr;
        };
    }
}
