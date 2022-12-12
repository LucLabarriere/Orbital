#pragma once
#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/PhysicsEngineInterface.h"

namespace Orbital
{
	class Entity;
	class PhysicsComponent;
	using EntityID = UUID;
	enum class ColliderType;

	using ECSManagerServices = Services<AccessPhysicsEngine>;

	/**
	 * @class ECSManager
	 * @brief Wrapper class around ECS::Registry
	 */
	class OENGINE_API ECSManager : public std::enable_shared_from_this<ECSManager>, protected ECSManagerServices
	{
	public:
		ECSManager(const SharedApplication& app) : ECSManagerServices(app), mRegistry(){};
		~ECSManager(){};

		/**
		 *  @brief deletes all pools
		 *
		 * Releases the memory so that the registry is unusable after, unless registerComponentType is called again
		 *
		 */
		inline void cleanUp()
		{
			mRegistry.cleanUp();
		}

		/**
		 * @brief Removes all components and entities
		 */
		inline void reset()
		{
			mRegistry.reset();
		}

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
		std::unordered_map<EntityID, T>& components()
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
	const T& SafeHandle<T>::operator*() const
	{
		const ECS::Registry* registry = mManager.lock()->getRegistry();
		ECS::Handle<T> component = registry->get<T>(mEntityID);
		assert(component.isValid());

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

	template <typename T>
	const TemporaryHandle<T> SafeHandle<T>::getTemporary() const
	{
		const T* object = operator->();
		return TemporaryHandle<T>(object, mEntityID, mManager);
	}

	template <typename T>
	TemporaryHandle<T> SafeHandle<T>::getTemporary()
	{
		T* object = operator->();
		return TemporaryHandle<T>(object, mEntityID, mManager);
	}

	template <typename T>
	const T& TemporaryHandle<T>::operator*() const
	{
		return *mObject;
	}

	template <typename T>
	const T* TemporaryHandle<T>::operator->() const
	{
		return mObject;
	}

	template <typename T>
	T& TemporaryHandle<T>::operator*()
	{
		return *mObject;
	}

	template <typename T>
	T* TemporaryHandle<T>::operator->()
	{
		return mObject;
	}
	template <typename T>
	bool TemporaryHandle<T>::isValid() const
	{
		Logger::Critical("TemporaryHandle::isValid not implemented");
		return false;
	}
} // namespace Orbital
