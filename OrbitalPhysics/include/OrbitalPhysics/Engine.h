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
			~Engine(){};

			void initialize()
			{
				mCollisions.reserve(10000);
			}

			void terminate(){};

			/**
			 * @brief Adds a collider to the engine
			 *
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @return Weak pointer to the collider
			 */
			template <typename T>
			std::weak_ptr<T> push();

			/**
			 * @brief Adds a collider to the engine
			 *
			 * @param transform : Transform to be copied
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @return Weak pointer to the collider
			 */
			template <typename T>
			std::weak_ptr<T> push(const Transform& transform);

			template <typename T>
			std::weak_ptr<T> cast(const std::weak_ptr<Collider>& collider);

			void onUpdate(float seconds)
			{
				for (size_t i = 0; i < mColliders.size(); i++)
				{
					for (size_t j = i + 1; j < mColliders.size(); j++)
					{
						mCollisions.push_back(mColliders[i]->checkCollision(*mColliders[j]));
					}
				}

				for (auto& collision : mCollisions)
				{
					//collision.trigger();
				}

				mCollisions.clear();
			}

		private:
			std::vector<std::shared_ptr<Collider>> mColliders;
			std::vector<CollisionData> mCollisions;
		};

	} // namespace Physics
} // namespace Orbital
