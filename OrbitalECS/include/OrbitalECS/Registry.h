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

        template<typename T>
        void registerType()
        {
            ComponentContainer<T>* container = new ComponentContainer<T>();

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
            Logger::Debug("In Register->push. Getting the reference...");
            ComponentContainer<T>* pool = static_cast<ComponentContainer<T>*>(mPools[typeid(T).hash_code()]);
            T& reference = pool->push(args...);
            Logger::Debug("Got the reference.Getting the handle...");
            Handle<T> handle(reference);
            Logger::Debug("Got the handle. Returning...");
            return Handle<T>(reference);
        }

    private:
        std::unordered_map<std::size_t, void*> mPools;
        std::vector<std::function<void()>> mDestructors;
    };
}
