#pragma once

#include <memory>
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    class OrbitalApplication;

    namespace Services
    {
        template <typename T>
        class RawService
        {
        protected:
            static inline T* Get() { return sPtr; }
            static void Initialize(T* service) { sPtr = service; }

            static inline T* sPtr = nullptr;
        };

        template <typename T>
        class SharedService
        {
        protected:
            static inline std::weak_ptr<T> Get() { return sPtr; }
            static void Initialize(std::shared_ptr<T> service) { sPtr = service; }

            static inline std::shared_ptr<T> sPtr = nullptr;
        };

        template <typename T>
        class UniqueService 
        {
        protected:
            template <typename ...Args>
            static void Initialize(Args... args) { LOGFUNC(); sPtr = std::unique_ptr<T>(new T(args...)); }

            static inline std::unique_ptr<T> sPtr = nullptr;
        };
    }
}
