#include "OrbitalPhysics/Engine.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		template <typename T>
		std::weak_ptr<T> Engine::push()
		{
			std::shared_ptr<T> collider = std::make_shared<T>(T::GetColliderType());
			mColliders.push_back(static_pointer_cast<Collider>(collider));
			collider->setId(mColliders.size() - 1);

			return collider;
		}

		template <typename T>
		std::weak_ptr<T> Engine::push(const Transform& transform)
		{
			std::shared_ptr<T> collider = std::make_shared<T>(T::GetColliderType(), transform);
			mColliders.push_back(std::static_pointer_cast<Collider>(collider));
			collider->setId(mColliders.size() - 1);

			return collider;
		}

		template <typename T>
		std::weak_ptr<T> Engine::cast(const std::weak_ptr<Collider>& collider)
		{
			if (T::GetColliderType() == collider.lock()->getColliderType())
			{
				return std::static_pointer_cast<T>(collider.lock());
			}
			return std::weak_ptr<T>();
		}

		template std::weak_ptr<PointCollider> Engine::push();
		template std::weak_ptr<SphereCollider> Engine::push();
		template std::weak_ptr<PointCollider> Engine::push(const Transform& transform);
		template std::weak_ptr<SphereCollider> Engine::push(const Transform& transform);
		template std::weak_ptr<SphereCollider> Engine::cast(const std::weak_ptr<Collider>& collider);
		template std::weak_ptr<PointCollider> Engine::cast(const std::weak_ptr<Collider>& collider);
	} // namespace Physics
} // namespace Orbital
