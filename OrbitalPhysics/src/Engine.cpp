#include "OrbitalPhysics/Engine.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		template <typename T>
		WeakRef<T> Engine::push()
		{
			Ref<T> collider = MakeRef<T>(T::GetColliderType());
			mColliders.push_back(static_pointer_cast<Collider>(collider));
			collider->setId(mColliders.size() - 1);

			return collider;
		}

		template <typename T>
		WeakRef<T> Engine::push(const Transform& transform)
		{
			Ref<T> collider = MakeRef<T>(T::GetColliderType(), transform);
			mColliders.push_back(std::static_pointer_cast<Collider>(collider));
			collider->setId(mColliders.size() - 1);

			return collider;
		}

		template <typename T>
		WeakRef<T> Engine::cast(const WeakRef<Collider>& collider)
		{
			if (T::GetColliderType() == collider.lock()->getColliderType())
			{
				return std::static_pointer_cast<T>(collider.lock());
			}
			return WeakRef<T>();
		}

		template WeakRef<PointCollider> Engine::push();
		template WeakRef<SphereCollider> Engine::push();
		template WeakRef<PointCollider> Engine::push(const Transform& transform);
		template WeakRef<SphereCollider> Engine::push(const Transform& transform);
		template WeakRef<SphereCollider> Engine::cast(const WeakRef<Collider>& collider);
		template WeakRef<PointCollider> Engine::cast(const WeakRef<Collider>& collider);
	} // namespace Physics
} // namespace Orbital
