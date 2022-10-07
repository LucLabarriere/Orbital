#pragma once
#include "OrbitalECS/Context.h"
#include "OrbitalLogger/Logger.h"
#include <unordered_map>

namespace Orbital
{
    template<typename T>
    class Pool
    {
    public:
        Pool() {  };
        ~Pool() {  }

        /**
         * @brief Creates a component inplace and returns a reference to it
         *
         * @tparam Args 
         * @param args 
         * @return T&
         */
        template<typename ...Args>
        T& push(Args... args)
        {
            sId += 1;
            return mObjects.try_emplace(sId - 1, args...).first->second;
        }

    private:
        static inline std::size_t sId = 0;
        std::unordered_map<std::size_t, T> mObjects;
    };
}
