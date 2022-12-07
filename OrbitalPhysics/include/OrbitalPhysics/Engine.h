#pragma once
#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"

namespace Orbital
{
	namespace Physics
	{
		class OPHYSICS_API Engine
		{
		public:
			Engine() : mColliders(){};
            ~Engine() {};

			void initialize()
			{
				LOGFUNC();
				mCollisions.reserve(10000);
			}

			void terminate(){};

			void push(const std::shared_ptr<Collider>& collider)
			{
				mColliders.push_back(collider);
			}

			void onUpdate(float seconds)
			{
				LOGFUNC();
				for (size_t i = 0; i < mColliders.size(); i++)
				{
					for (size_t j = i + 1; j < mColliders.size(); j++)
					{
						mCollisions.push_back(mColliders[i]->checkCollision(*mColliders[j]));
					}
				}

				for (auto& collision: mCollisions)
				{
					collision.trigger();
				}

				mCollisions.clear();
			}

		private:
			std::vector<std::shared_ptr<Collider>> mColliders;
			std::vector<CollisionData> mCollisions;
		};
	} // namespace Physics
} // namespace Orbital
