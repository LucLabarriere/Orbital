#pragma once
#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"

namespace Orbital
{
	namespace Physics
	{
		using ColliderID = Orbital::UUID;

		class ORBITAL_PHYSICS_API Engine
		{
		public:
			Engine() : mColliders() { LOGFUNC(); };
			~Engine(){};

			void initialize() { mCollisions.reserve(10000); }

			void terminate(){};

			/**
			 * @brief Adds a collider to the engine
			 *
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @return ID of the Collider
			 */
			template <typename T>
			auto push() -> ColliderID;

			/**
			 * @brief Adds a collider to the engine
			 *
			 * @param transform : Transform to be copied
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @reeturn ID of the Collider
			 */
			template <typename T>
			auto push(const Transform& transform) -> ColliderID;

			/**
			 * @brief Adds a collider to the engine at id
			 *
			 * @param id : The ColliderID
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @return ID of the Collider
			 */
			template <typename T>
			auto pushAt(const ColliderID& id) -> ColliderID;

			/**
			 * @brief Adds a collider to the engine at id
			 *
			 * @param transform : Transform to be copied
			 * @param id : The ColliderID
			 * @tparam T Collider type : PointCollider, SphereCollider, etc.
			 * @reeturn ID of the Collider
			 */
			template <typename T>
			auto pushAt(const ColliderID& id, const Transform& transform) -> ColliderID;

			// template <typename T>
			// WeakRef cast(const WeakRef<Collider>& collider);

			void update(float seconds);

			auto getCollider(const ColliderID& id) -> Collider&
			{
				return *mColliders.find(id)->second;
			}

			template <typename T>
			auto getCastedCollider(const ColliderID& id) -> T&
			{
				auto& collider = getCollider(id);
				Orbital::Assert(
					collider.getColliderType() == T::GetColliderType(),
					"Trying to cast a collider of unmatching type"
				);

				return static_cast<T&>(collider);
			}

			void clearColliders();
			void clearColliders(const ColliderID& id);

		private:
			std::map<ColliderID, Ref<Collider>> mColliders;
			std::vector<CollisionData> mCollisions;
		};
	} // namespace Physics
} // namespace Orbital
