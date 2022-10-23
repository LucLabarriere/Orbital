#pragma once

#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
    class OrbitalApplication;
    class SceneManager;

    struct OENGINE_API ScenesService
    {
    public:
        struct OENGINE_API ScenesInterface : public ServiceInterface<SceneManager>
        {
        public:
            ScenesInterface(std::shared_ptr<SceneManager> instance);

            void OnLoad();
            void OnCleanUp();
            void OnStart();
            void OnUpdate(const Time& dt);

        protected:
            friend Orbital::OrbitalApplication;

            void Terminate();
        } Scenes = ScenesInterface(nullptr);
    };
}
