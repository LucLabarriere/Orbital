#pragma once
#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"

namespace Orbital
{
	namespace Physics
	{
		using ColliderID = Orbital::UUID;

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
			 * @return ID of the Collider
			 */
			template <typename T>
			ColliderID push();

			/**
			 * @brief Adds a collider to the engine
			 *
			 * @param transform : Transform to be copied
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @reeturn ID of the Collider
			 */
			template <typename T>
			ColliderID push(const Transform& transform);

			/**
			 * @brief Adds a collider to the engine at id
			 *
			 * @param id : The ColliderID
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @return ID of the Collider
			 */
			template <typename T>
			ColliderID pushAt(const ColliderID& id);

			/**
			 * @brief Adds a collider to the engine at id
			 *
			 * @param transform : Transform to be copied
			 * @param id : The ColliderID
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @reeturn ID of the Collider
			 */
			template <typename T>
			ColliderID pushAt(const ColliderID& id, const Transform& transform);

			// template <typename T>
			// WeakRef cast(const WeakRef<Collider>& collider);

			void onUpdate(float seconds);

			Collider& getCollider(const ColliderID& id)
			{
				return *mColliders.find(id)->second;
			}

			template <typename T>
			T& getCastedCollider(const ColliderID& id)
			{
				auto& collider = getCollider(id);
				Orbital::Assert(
					collider.getColliderType() == T::GetColliderType(), "Trying to cast a collider of unmatching type"
				);

				return static_cast<T&>(collider);
			}

			void clearColliders();

		private:
			std::map<ColliderID, Ref<Collider>> mColliders;
			std::vector<CollisionData> mCollisions;
		};

	} // namespace Physics
} // namespace Orbital
