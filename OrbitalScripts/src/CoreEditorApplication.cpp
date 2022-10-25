#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity, ScriptServiceManager services)
		: NativeScript(baseEntity, services)
	{
	}


	void CoreEditorApplication::onLoad()
	{
		size_t entityCountW = 10;
		float xIncrement = 2.0f / (float)entityCountW;
		float yIncrement = 2.0f / (float)entityCountW;
		float scale = xIncrement * 0.1f;
		float xOffset = -0.99f;
		float yOffset = -0.99f;

		for (size_t i = 0; i < entityCountW; i++)
		{
			for (size_t j = 0; j < entityCountW; j++)
			{
				auto e = mServices.ECS.CreateEntity();
				auto manager = e.get<NativeScriptManager>();
				auto t = e.push<TransformComponent>();

				float xPos = xOffset + i * xIncrement;
				float yPos = yOffset + j * yIncrement;

				t->position.x = xPos;
				t->position.y = yPos;
				t->scale *= scale;

				MeshType meshType;

				if (i == 0 and j == 0)
				{
					manager->push("PlayerController", e);
					meshType = MeshType::Triangle;
				}
				else
				{
					meshType = (MeshType)Maths::Round(Random::Get());
				}

				auto m = e.push<MeshComponent>(meshType, t);
			}
		}
	}

	void CoreEditorApplication::onStart()
	{
	}

	void CoreEditorApplication::onUpdate(const Time& dt)
	{

	}
} // namespace Orbital

OE_DEFINE_CREATOR(CoreEditorApplication);
