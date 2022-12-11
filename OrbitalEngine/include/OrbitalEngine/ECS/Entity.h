#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Handle.h"

namespace Orbital
{
	namespace Physics
	{
		struct Transform;
	}
	using TransformComponent = Physics::Transform;
	class PhysicsComponent;
	class NativeScript;

	class OENGINE_API Entity
	{
	public:
		Entity(){};
		Entity(const EntityID& id, const std::weak_ptr<ECSManager>& manager);
		Entity(const Entity& other);

		template <typename T, typename... Args>
		SafeHandle<T> push(Args... args)
		{
			assert(get<T>().isValid() == false && "Entity already has the requested component");
			ECS::Registry* registry = mManager.lock()->getRegistry();
			registry->push<T>(mEntityID, args...);

			return SafeHandle<T>(mEntityID, mManager);
		}

		void pushNativeScript(const std::string& name);

		template <typename T>
		const SafeHandle<T> get() const
		{
			return SafeHandle<T>(mEntityID, mManager);
		}

		template <typename T>
		SafeHandle<T> get()
		{
			return SafeHandle<T>(mEntityID, mManager);
		}

		template <typename T>
		void remove()
		{
			assert(get<T>().isValid() == true && "Trying to remove a non existing component");

			if constexpr (std::is_same_v<PhysicsComponent, T>)
			{
				return removePhysicsComponent();
			}
			else if constexpr (std::is_same_v<TransformComponent, T>)
			{
				return removeTransformComponent();
			}

			return mManager.lock()->getRegistry()->remove<T>(mEntityID);
		}

		void removePhysicsComponent();
		void removeTransformComponent();
		void destroy();

	private:
		const EntityID mEntityID = 0;
		std::weak_ptr<ECSManager> mManager;
	};
} // namespace Orbital
