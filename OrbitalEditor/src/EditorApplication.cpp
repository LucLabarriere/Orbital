#include "OrbitalEditor/EditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalTools/Random.h"
#include "OrbitalScripts/PlayerController.h"

namespace Orbital
{
    EditorApplication::EditorApplication()
        : OrbitalApplication()
    {

    }
    
    void EditorApplication::initialize()
    {
        OrbitalApplication::initialize();

        // Registering component types
        mRegistry.registerComponentType<TransformComponent>();
        mRegistry.registerComponentType<MeshComponent>();
        mRegistry.registerComponentType<NativeScriptManager>();
        mScriptsLibrary.registerScript("PlayerController");
        
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
                auto manager = e.push<NativeScriptManager>(&mScriptsLibrary);
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
                    manager->push("PlayerController", e);
                }
            }
        }
    }

    void EditorApplication::terminate()
    {
        OrbitalApplication::terminate();
    }

    void EditorApplication::update(Time dt)
    {
        for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
        {
            manager.onUpdate(dt);
        }

        for (auto& [ uuid, mc ] : mRegistry.components<MeshComponent>())
        {
            mHighRenderer.draw(mc);
        }
    }

    bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
    {
        if (e.getKey() == OE_KEY_ESCAPE)
        {
            Logger::Log("Reloading scripts");

            // Reset all scripts but keep the managers intact to reconstruct
            for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
            {
                std::vector<std::string> names = manager.getScriptNames();
                if (names.size() != 0)
                {
                    manager.clearPointers();
                }
            }

            mScriptsLibrary.reload();

            // Reset the managers and refill them
            for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
            {
                std::vector<std::string> names = manager.getScriptNames();
                if (names.size() != 0)
                {
                    manager.clearContainer();
                    
                    for (auto& name : names)
                    {
                        manager.push(name, mRegistry.getEntity(uuid));
                    }
                }
            }

            Logger::Trace("Done reloading scripts");
        }

        return true;
    }
}
