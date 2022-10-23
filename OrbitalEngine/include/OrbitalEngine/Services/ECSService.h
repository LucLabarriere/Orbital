#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
    class OrbitalApplication;
    class Scene;

    struct ECSService
    {
    public:
        class ECSInterface: public ServiceInterface<Scene>
        {
        public:
            ECSInterface();
            ECSInterface(std::shared_ptr<Scene> instance);

            void Reset();
            [[nodiscard]] Entity CreateEntity();
            Entity GetEntity(const EntityID& entityID);

            template<typename T>
            void RegisterComponentType()
            {
                LOGVAR(mInstance == nullptr);
                LOGVAR(mRegistry == nullptr);
                mRegistry->registerComponentType<T>();
            }

            template<typename T>
            std::unordered_map<EntityID, T>& Components()
            {
                return mRegistry->components<T>();
            }

        private:
            std::shared_ptr<Registry> mRegistry;
        } ECS = ECSInterface();
    };
}
