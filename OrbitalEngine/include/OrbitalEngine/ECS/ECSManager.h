#pragma once
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/Services/RendererInterface.h"

namespace Orbital
{
	class Entity;
	class PhysicsComponent;
	enum class ColliderType;

	using ECSManagerServices = Services<AccessPhysicsEngine, AccessRenderer>;

	/**
	 * @class ECSManager
	 * @brief Wrapper class around ECS::Registry
	 */
	class OENGINE_API ECSManager : public std::enable_shared_from_this<ECSManager>, protected ECSManagerServices
	{
	public:
		ECSManager(const SharedApplication& app) : ECSManagerServices(app), mRegistry()
		{
			ECSManagerServices::InitializeServices();
		}
		~ECSManager(){};

		/**
		 *  @brief deletes all pools
		 *
		 * Releases the memory so that the registry is unusable after, unless registerComponentType is called again
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
		inline void registerComponentType()
		{
			mRegistry.registerComponentType<T>();
		}

		/**
		 * @brief Creates an entity
		 *
		 * @return Entity
		 */
		Entity createEntity();

		/**
		 * @brief deletes the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 */
		void deleteEntity(const EntityID& id);

		/**
		 * @brief returns the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 * @return Entity
		 */
		Entity getEntity(const EntityID& id);

		template <typename T>
		ECS::ComponentContainer<T>& components()
		{
			// TODO : make work with transforms, scripts, etc
			return mRegistry.components<T>();
		}

		bool isEntityValid(const EntityID& id) const
		{
			return mRegistry.isEntityValid(id);
		}

		ECS::Registry* getRegistry()
		{
			return &mRegistry;
		}

		const ECS::Registry* getRegistry() const
		{
			return &mRegistry;
		}

		SafeHandle<PhysicsComponent> addPhysicsComponent(const EntityID& id, ColliderType colliderType);

	private:
		ECS::Registry mRegistry;
	};

	// SafeHandle IMPLEMENTATIONS

	template <typename T>
	const T& SafeHandle<T>::get() const
	{
		return operator*();
	}

	template <typename T>
	T& SafeHandle<T>::get()
	{
		return operator*();
	}

	template <typename T>
	const T& SafeHandle<T>::operator*() const
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<T> component = registry->get<T>(mEntityID);
		Orbital::Assert(component.isValid(), "The component " + std::string(typeid(T).name()) + " is not valid");

		return *component;
	}

	template <typename T>
	T& SafeHandle<T>::operator*()
	{
		return OE_UNCONST(T&, SafeHandle<T>, operator*);
	}

	template <typename T>
	const T* SafeHandle<T>::operator->() const
	{
		return &operator*();
	}

	template <typename T>
	T* SafeHandle<T>::operator->()
	{
		return &operator*();
	}

	template <typename T>
	bool SafeHandle<T>::isValid() const
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<T> component = registry->get<T>(mEntityID);

		return component.isValid();
	}
} // namespace Orbital
