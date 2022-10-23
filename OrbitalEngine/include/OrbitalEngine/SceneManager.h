#pragma once

#include "OrbitalEngine/Scene.h"

namespace Orbital
{
    class OENGINE_API SceneManager
    {
    public:
        /**
         * @brief Initializes the scene with appropriate services
         *
         * @param services
         */
        SceneManager(SceneServiceManager services);

        void terminate();

        void onLoad();
        void onCleanUp();
        void onStart();
        void onUpdate(const Time& dt);

        std::shared_ptr<Scene> getCurrentScene() const { return mScene; }

    private:
        SceneServiceManager mServices;
        std::shared_ptr<Scene> mScene;
    };
}
