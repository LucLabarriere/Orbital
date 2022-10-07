#pragma once

#include "OrbitalECS/Context.h"
#include "OrbitalECS/Handle.h"
#include "OrbitalECS/Pool.h"

namespace Orbital
{

    class Registry
    {
    public:
        Registry() {  }
        ~Registry()
        {
            for (auto& destructor : mDestructors)
            {
                destructor();
            }
        }

        /**
         * @brief Registers the type T in the ECS Registry
         *
         * @tparam T 
         */
        template<typename T>
        void registerType()
        {
            Pool<T>* container = new Pool<T>();

            mPools.insert({ typeid(T).hash_code(), (void*)container });
            mDestructors.push_back([container](){
                    delete container;
            });
        }

        /**
         * @brief Creates the component in place
         *
         * @param args The arguments required to build the component
         * @return Handle<T>
         */
        template<typename T, typename ...Args>
        Handle<T> push(Args... args)
        {
            Pool<T>* pool = static_cast<Pool<T>*>(mPools[typeid(T).hash_code()]);
            auto [uuid, object] = pool->push(args...);
            return Handle<T>(object, uuid);
        }

        /**
         * @brief Returns the requested Component
         *
         * @tparam T 
         * @param uuid 
         * @return Handle<T>
         */
        template<typename T>
        Handle<T> get(const UUID& uuid)
        {

            Pool<T>* pool = static_cast<Pool<T>*>(mPools[typeid(T).hash_code()]);
            return Handle<T>(pool->get(uuid), uuid);
        }

    private:
        std::unordered_map<std::size_t, void*> mPools;
        std::vector<std::function<void()>> mDestructors;
    };
}
