#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"
#include "OrbitalEngine/Services/ScenesInterface.h"
#include "OrbitalEngine/Services/SettingsInterface.h"

namespace Orbital
{
	using EntityServices = Services<
		AccessECS, AccessScenes, AccessPhysicsEngine, AccessRenderer, AccessSettings>;

	/**
	 * @class Entity
	 * @brief Convinience class to work on an EntityID
	 */
	class ORBITAL_ENGINE_API Entity : protected EntityServices
	{
	public:
		Entity() = default;
		Entity(
			const SharedApplication& app, const EntityID& id,
			const WeakRef<ECSManager>& manager
		);
		Entity(const SharedApplication& app, const Entity& other);
		virtual ~Entity() = default;

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
		auto push(Args&&... args) -> SafeHandle<T>
		{
			Orbital::Assert(
				get<T>().isValid() == false, "Entity already has the requested component"
			);
			ECS::Registry* registry = mManager.lock()->getRegistry();
			if constexpr (std::is_base_of_v<Component, T>)
				registry->push<T>(mEntityID, getComponentArgs(), args...);
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
		auto get() const -> const SafeHandle<T>
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
		auto get() -> SafeHandle<T>
		{
			return SafeHandle<T>(mEntityID, mManager);
		}

		auto getComponentArgs() -> Component::InitArgs { return { mEntityID, mManager }; }

		/**
		 * @brief Removes the component from any of the pools
		 *
		 * @tparam T The component type
		 */
		template <typename T>
		void remove()
		{
			Orbital::Assert(
				get<T>().isValid() == true, "Trying to remove a non existing component"
			);

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

		inline auto getEntityID() const -> const EntityID& { return mEntityID; }

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
		void pushNativeScript(std::string_view name);

	protected:
		EntityID mEntityID = 0;

	private:
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital
