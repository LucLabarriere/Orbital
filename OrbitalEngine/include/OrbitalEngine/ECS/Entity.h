#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"

namespace Orbital
{
	namespace Physics
	{
		struct Transform;
	}
	using TransformComponent = Physics::Transform;
	class PhysicsComponent;
	class NativeScript;

	using EntityServices = Services<AccessECS, AccessScenes, AccessPhysicsEngine, AccessRenderer>;

	/**
	 * @class Entity
	 * @brief Convinience class to work on an EntityID
	 */
	class OENGINE_API Entity : protected EntityServices
	{
	public:
		Entity(){};
		Entity(const SharedApplication& app, const EntityID& id, const WeakRef<ECSManager>& manager);
		Entity(const SharedApplication& app, const Entity& other);

		/**
		 * @brief Attaches a component to the entity
		 * This is done either by adding it to an component pool
		 * Or adding it to another pool such as NativeScriptManager
		 *
		 * @tparam T The component type
		 * @tparam Args Arguments to create the component
		 * @return SafeHandle<T>
		 */
		template <typename T, typename... Args>
		SafeHandle<T> push(Args... args)
		{
			assert(get<T>().isValid() == false && "Entity already has the requested component");
			ECS::Registry* registry = mManager.lock()->getRegistry();
			if constexpr(std::is_base_of_v<Component, T>)
				registry->push<T>(mEntityID, mEntityID, mManager, args...);
			else
				registry->push<T>(mEntityID, args...);

			return SafeHandle<T>(mEntityID, mManager);
		}

		/**
		 * @brief Returns a SafeHandle to the component
		 *
		 * @tparam T The component type
		 * @return SafeHandle<T>
		 */
		template <typename T>
		const SafeHandle<T> get() const
		{
			return SafeHandle<T>(mEntityID, mManager);
		}

		/**
		 * @brief Returns a SafeHandle to the component
		 *
		 * @tparam T The component type
		 * @return SafeHandle<T>
		 */
		template <typename T>
		SafeHandle<T> get()
		{
			return SafeHandle<T>(mEntityID, mManager);
		}

		/**
		 * @brief Removes the component from any of the pools
		 *
		 * @tparam T The component type
		 */
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

		/**
		 * @brief Destroys the entity
		 */
		void destroy();

	private:
		/**
		 * @brief Removes the PhysicsComponent
		 */
		void removePhysicsComponent();

		/**
		 * @brief Removes the TransformComponent
		 */
		void removeTransformComponent();

		/**
		 * @brief Adds a script to the NativeScriptManager
		 *
		 * @param name : Name of the script
		 */
		void pushNativeScript(const std::string& name);

		const EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital
