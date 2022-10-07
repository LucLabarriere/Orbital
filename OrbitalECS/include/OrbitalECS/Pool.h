#pragma once
#include "OrbitalECS/Context.h"
#include "OrbitalTools/UUID.h"
#include "OrbitalLogger/Logger.h"
#include <tuple>

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
        std::tuple<UUID, T&> push(Args... args)
        {
            UUID uuid;
            T& object = mObjects.try_emplace(uuid, args...).first->second;

            return { uuid, object };
        }

        T& get(const UUID& uuid)
        {
            auto object = mObjects.find(uuid);
            if (object != mObjects.end())
                return object->second;
        }

    private:
        std::unordered_map<UUID, T> mObjects;
    };
}
