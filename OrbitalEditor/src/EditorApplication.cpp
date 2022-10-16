#include "OrbitalEditor/EditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalTools/Random.h"
#include <dlfcn.h>

namespace Orbital
{
    EditorApplication::EditorApplication()
        : OrbitalApplication()
    {
        //mScriptsLibrary = dlopen("/home/lucla/Programming/OrbitalRefactoring/build/Debug/OrbitalScripts/libOrbitalScripts.so", RTLD_LAZY);

        //if (!mScriptsLibrary)
        //{
        //    Logger::Error(dlerror());
        //}
    }
    
    void EditorApplication::initialize()
    {
        OrbitalApplication::initialize();

        //dlerror();    /* Clear any existing error */

        //CreatePlayerController_t* createPlayerController = (CreatePlayerController_t*)dlsym(mScriptsLibrary, "CreatePlayerController");
        //const char* dlsym_error = dlerror();

        //if (dlsym_error) {
        //    Logger::Error("Cannot load symbol CreatePlayerController: ",  dlsym_error);
        //}
        //
        //DestroyPlayerController_t* destroyPlayerController = (DestroyPlayerController_t*)dlsym(mScriptsLibrary, "DestroyPlayerController");

        //dlsym_error = dlerror();
        //if (dlsym_error) {
        //    Logger::Error("Cannot load symbol DestroyPlayerController: ", dlsym_error);
        //}

        // Registering component types
        mRegistry.registerComponentType<TransformComponent>();
        mRegistry.registerComponentType<MeshComponent>();
        //mRegistry.registerComponentType<PlayerController*>();

        Entity e = mRegistry.createEntity();

        size_t entityCountW = 10;
        float xIncrement = 1.0f / (float)entityCountW;
        float yIncrement = 1.0f / (float)entityCountW;
        float scale = xIncrement * 0.8f;
        float xOffset = -0.5f;
        float yOffset = -0.5f;

        for (size_t i = 0; i < entityCountW; i++)
        {
            for (size_t j = 0; j < entityCountW; j++)
            {
                auto e = mRegistry.createEntity();
                auto t = e.push<TransformComponent>();
                
                float xPos = xOffset + i * xIncrement;
                float yPos = yOffset + j * yIncrement;

                t->position.x = xPos;
                t->position.y = yPos;
                t->scale *= scale;

                MeshType meshType = (MeshType)Maths::Round(Random::Get());
                auto m = e.push<MeshComponent>(meshType, t);

                if (i == 0 and j == 0)
                {
                    //e.push<PlayerController*>(createPlayerController(e));
                    //auto test  = createPlayerController(e);
                    //delete test;
                }
            }
        }
    }

    void EditorApplication::terminate()
    {
        //dlclose(mScriptsLibrary);
        OrbitalApplication::terminate();
    }

    void EditorApplication::update(Time dt)
    {

        for (auto& [ uuid, mc ] : mRegistry.components<MeshComponent>())
        {
            mc.getTransform()->rotation.z += 2.0f * dt.seconds();
            mHighRenderer.draw(mc);
        }
    }

}
