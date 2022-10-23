#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalECS/ECS.h"

#include "OrbitalEngine/Services/ServiceManager.h"

namespace Orbital
{
    class SceneManager;

    class OENGINE_API Scene 
    {
    public:

        /**
         * @brief Initializs the Scene with the appropriate services
         *
         * @param services
         */
        Scene(SceneServiceManager services);

        void terminate();
        void reset();

        Entity createEntity();

        void onLoad();
        void onCleanUp();
        void onStart();
        void onUpdate(const Time& dt);

    protected:
        friend ECSService;
        friend SceneManager;

        SceneServiceManager mServices;
        std::shared_ptr<Registry> mRegistry;
    };
}
