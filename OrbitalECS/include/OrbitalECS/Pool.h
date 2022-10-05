#pragma once
#include "OrbitalECS/Context.h"
#include "OrbitalLogger/Logger.h"
#include <unordered_map>

namespace Orbital
{
    template<typename T>
    class ComponentContainer
    {
    public:
        ComponentContainer() {  };
        ~ComponentContainer() { Logger::Debug("Destroying ComponentContainer: ", typeid(T).name()); }

        /**
         * @brief Creates a component inplace and returns a reference to it
         *
         * @tparam Args 
         * @param args  The arguments required to build the component
         * @return T&
         */
        template<typename ...Args>
        T& push(Args... args)
        {
            Logger::Debug("In Pool->push. Emplacing...");
            sId += 1;
            T& toreturn = mObjects.try_emplace(sId - 1, args...).first->second;
            Logger::Debug("Emplaced. Returning...");
            return toreturn;
        }

    private:
        static inline std::size_t sId = 0;
        std::unordered_map<std::size_t, T> mObjects;
    };
}
