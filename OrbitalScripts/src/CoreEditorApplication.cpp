#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalTools/Random.h"
#include "OrbitalEngine/Scene.h"

namespace Orbital
{
    CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity)
        : NativeScript(baseEntity)
    {

    }

    void CoreEditorApplication::onLoad() 
    {
        size_t entityCountW = 10;
        float xIncrement = 1.0f / (float)entityCountW;
        float yIncrement = 1.0f / (float)entityCountW;
        float scale = xIncrement * 0.7f;
        float xOffset = -0.5f;
        float yOffset = -0.5f;

        for (size_t i = 0; i < entityCountW; i++)
        {
            for (size_t j = 0; j < entityCountW; j++)
            {
                auto e = Services::Scene::CreateEntity();
                auto manager = e.push<NativeScriptManager>();
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

    void CoreEditorApplication::onStart() 
    {

    }

    void CoreEditorApplication::onUpdate(const Time& dt) 
    {

    }
}

OE_DEFINE_CREATOR(CoreEditorApplication);

