#pragma once
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"

namespace Orbital
{
	using ECSManagerServices = Services<AccessPhysicsEngine, AccessRenderer>;

	/**
	 * @class ECSManager
	 * @brief Wrapper class around ECS::Registry
	 */
	class ORBITAL_ENGINE_API ECSManager : public std::enable_shared_from_this<ECSManager>,
										  protected ECSManagerServices
	{
	public:
		ECSManager(const SharedApplication& app) : ECSManagerServices(app), mRegistry()
		{
			ECSManagerServices::InitializeServices();
			mRequestedDeletes.reserve(50);
		}
		virtual ~ECSManager() = default;

		/**
		 *  @brief deletes all pools
		 *
		 * Releases the memory so that the registry is unusable after, unless
		 * registerComponentType is called again
		 *
		 */
		void cleanUp();

		/**
		 * @brief Removes all components and entities
		 */
		void reset();

		/**
		 * @brief Registers the type T in the ECS Registry
		 *
		 * @tparam T
		 */
		template <typename T>
		void registerComponentType()
		{
			mRegistry.registerComponentType<T>();
		}

		/**
		 * @brief Creates an entity
		 *
		 * @return Entity
		 */
		auto createEntity() -> Entity;

		/**
		 * @brief deletes the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 */
		void deleteEntity(const EntityID& id);

		/**
		 * @brief request to delete the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 */
		void requestDeleteEntity(const EntityID& id);

		/**
		 * @brief Checks if the entity exists
		 * @param id the UUID of the entity
		 * @return true if the entity exists
		 */
		auto entityExists(const EntityID& id) -> bool;

		/**
		 * @brief returns the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 * @return Entity
		 */
		auto getEntity(const EntityID& id) -> Entity;

		void deleteRequested();

		template <typename T>
		auto components() -> ECS::ComponentContainer<T>&
		{
			// TODO : make work with transforms, scripts, etc
			return mRegistry.components<T>();
		}

		auto isEntityValid(const EntityID& id) const -> bool
		{
			return mRegistry.isEntityValid(id);
		}

		auto getRegistry() -> ECS::Registry* { return &mRegistry; }

		auto getRegistry() const -> const ECS::Registry* { return &mRegistry; }

	private:
		ECS::Registry mRegistry;
		std::vector<EntityID> mRequestedDeletes;
	};

	// SafeHandle IMPLEMENTATIONS

	template <typename T>
	auto SafeHandle<T>::get() const -> const T&
	{
		return operator*();
	}

	template <typename T>
	auto SafeHandle<T>::get() -> T&
	{
		return operator*();
	}

	template <typename T>
	auto SafeHandle<T>::operator*() const -> const T&
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<T> component = registry->get<T>(mEntityID);
		Orbital::Assert(
			component.isValid(),
			"The component " + std::string(typeid(T).name()) + " is not valid"
		);

		return *component;
	}

	template <typename T>
	auto SafeHandle<T>::operator*() -> T&
	{
		return OE_UNCONST(T&, SafeHandle<T>, operator*);
	}

	template <typename T>
	auto SafeHandle<T>::operator->() const -> const T*
	{
		return &operator*();
	}

	template <typename T>
	auto SafeHandle<T>::operator->() -> T*
	{
		return &operator*();
	}

	template <typename T>
	auto SafeHandle<T>::isValid() const -> bool
	{
		if (mManager.expired()) return false;

		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<T> component = registry->get<T>(mEntityID);

		return component.isValid();
	}
} // namespace Orbital
