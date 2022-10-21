#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalTools/Services.h"
#include "OrbitalTools/Time.h"
#include "OrbitalEngine/HighRenderer.h"

namespace Orbital
{
    namespace Services { class Scene; }
    class OrbitalApplication;

    class OENGINE_API Scene : private Services::Renderer
    {
    private:
        Scene();

        void terminate();
        void reset();

        void onLoad();
        void onCleanUp();
        void onStart();
        void onUpdate(const Time& dt);

    private:
        friend OrbitalApplication;
        friend Services::Scene;

        Registry mRegistry;
    };

    namespace Services
    {
        class Scene : private UniqueService<Orbital::Scene>
        {
        protected:
            [[nodiscard]] static inline Entity CreateEntity() { return sPtr->mRegistry.createEntity(); };
            static inline Entity GetEntity(const EntityID& entityID) { return sPtr->mRegistry.getEntity(entityID); }

            template<typename T>
            static inline void RegisterComponentType() { sPtr->mRegistry.registerComponentType<T>(); }

            template<typename T>
            static inline std::unordered_map<EntityID, T>& Components() { return sPtr->mRegistry.components<T>(); }

            static inline void Reset() { sPtr->reset(); }
            static inline void OnLoad() { sPtr->onLoad(); }
            static inline void OnCleanUp() { sPtr->onCleanUp(); }
            static inline void OnStart() { sPtr->onStart(); }
            static inline void OnUpdate(const Orbital::Time& dt) { sPtr->onUpdate(dt); }

        private:
            friend OrbitalApplication;

            static inline void Terminate() { sPtr->terminate(); }
        };
    }
}
