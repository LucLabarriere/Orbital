#pragma once

#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/ECSManager.h"

namespace Orbital
{
	class Health : public Component
	{
	public:
		Health(const Component::InitArgs& args) : Component(args)
		{
		}

		void getHit(float damage)
		{
			this->current -= damage;
			if (this->current <= this->min)
			{
				this->current = this->min;
				this->deathCallback();
			}
		}

		std::function<void(void)> deathCallback = [this]() { mManager.lock()->requestDeleteEntity(mEntityID); };
		float current = 100.0f;
		float max = 100.0f;
		float min = 0.0f;
	};
} // namespace Orbital
