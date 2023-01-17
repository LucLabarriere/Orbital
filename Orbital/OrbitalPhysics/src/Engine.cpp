#include "OrbitalPhysics/Engine.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		template <typename T>
		ColliderID Engine::push()
		{
			ColliderID id;

			return pushAt<T>(id);
		}

		template <typename T>
		ColliderID Engine::push(const Transform& transform)
		{
			ColliderID id;
			return pushAt<T>(id, transform);
		}

		template <typename T>
		ColliderID Engine::pushAt(const ColliderID& id)
		{
			mColliders.emplace(id, new T(id));

			return id;
		}

		template <typename T>
		ColliderID Engine::pushAt(const ColliderID& id, const Transform& transform)
		{
			mColliders.emplace(id, new T(id, transform));

			return id;
		}

		void Engine::update(float seconds)
		{
			for (auto& [idA, colA] : mColliders)
			{
				for (auto& [idB, colB] : mColliders)
				{
					if (idA == idB)
						break;

					mCollisions.emplace_back(colA->checkCollision(*colB));
				}
			}

			for (auto& collision : mCollisions)
			{
				if (collision.collide)
				{
					collision.A->triggerCollisionCallback(*mColliders[collision.B->getID()]);
					collision.B->triggerCollisionCallback(*mColliders[collision.A->getID()]);
				}
			}

			mCollisions.clear();
		}

		void Engine::clearColliders()
		{
			mColliders.clear();
		}

		void Engine::clearColliders(const ColliderID& id)
		{
			auto collider = mColliders.find(id);
			if (collider != mColliders.end())
				mColliders.erase(id);
		}

#define INSTANTIATE(x)                                                                                                 \
	template OPHYSICS_API ColliderID Engine::push<x>();                                                                             \
	template OPHYSICS_API ColliderID Engine::push<x>(const Transform& transform);                                                   \
	template OPHYSICS_API ColliderID Engine::pushAt<x>(const ColliderID& id);                                                       \
	template OPHYSICS_API ColliderID Engine::pushAt<x>(const ColliderID& id, const Transform& transform);

		INSTANTIATE(PointCollider);
		INSTANTIATE(SphereCollider);
	} // namespace Physics
} // namespace Orbital
