#pragma once

#include "OrbitalECS/Context.h"
#include "OrbitalTools/UUID.h"
#include "OrbitalLogger/Logger.h"
#include <unordered_map>

namespace Orbital
{
    using EntityID = UUID;
    class Entity;

    /**
     * @class Pool
     * @brief Contains all components of type T
     */

    class BasePool
    {
    public:
        BasePool() { }
        virtual ~BasePool() { }

        virtual void clear() = 0;
    };
    

    template<typename T>
    class Pool : public BasePool
    {
    public:
        Pool() : BasePool() {  }
        virtual ~Pool() override {  }

        /**
         * @brief Creates a component inplace and returns a reference to it
         *
         * @tparam Args 
         * @param id
         * @param args 
         * @return T&
         */
        template<typename ...Args>
        T& push(const EntityID id, Args... args)
        {
            return mObjects.try_emplace(id, args...).first->second;
        }

        /**
         * @brief Returns the component matching the EntityID
         *
         * @param id 
         * @return 
         */
        T* tryGet(const EntityID& id)
        {
            auto object = mObjects.find(id);

            if (object != mObjects.end())
                return &object->second;
            else
                return nullptr;
        }

        virtual void clear() override
        {
            mObjects.clear();
        }

        std::unordered_map<EntityID, T>& components() { return mObjects; }

    private:
        std::unordered_map<EntityID, T> mObjects;
    };


    /**
     * @class ComponentHandle
     * @brief Contains a pointer to the object and its EntityID
     */
    template<typename T>
    class ComponentHandle
    {
    public:
        ComponentHandle(Pool<T>* pool) : mObject(nullptr), mEntityID(0), mPool(pool) {  }
        ComponentHandle(T* object, EntityID id, Pool<T>* pool) : mObject(object), mEntityID(id), mPool(pool) {  }
        
        T* operator->() { return mObject; }
        T& operator*() { return *mObject; }
        bool isValid() const;
        const EntityID& getEntityID() const { return mEntityID; }

    private:
        T* mObject;
        Pool<T>* mPool;
        EntityID mEntityID;
    };

    /**
     * @class Registry
     * @brief Stores the component pools
     *
     */
    class OECS_API Registry
    {
    public:
        Registry() {  }
        ~Registry()
        {
            if (!mCleaned)
            {
                Logger::Error("Error, the registry was not cleaned before closing the app");
                cleanUp();
            }
        }

        /**
         * @brief deletes all pools
         * Releases the memory so that the registry is unusable after, unleast registerComponentType is called again
         */
        void cleanUp()
        {
            for (auto& [ id, pool ] : mPools)
            {
                delete pool;
            }

            mCleaned = true;
        }

        /**
         * @brief Removes all components and entities
         */
        void reset()
        {
            for (auto& [ id, pool ] : mPools)
            {
                pool->clear();
            }

            mEntities.clear();
        }

        /**
         * @brief Registers the type T in the ECS Registry
         *
         * @tparam T 
         */
        template<typename T>
        void registerComponentType()
        {
            Pool<T>* pool = new Pool<T>();

            mPools.insert({ typeid(T).hash_code(), dynamic_cast<BasePool*>(pool) });
        }

        /**
         * @brief Creates an entity
         *
         * @return Entity
         */
        Entity createEntity();

        /**
         * @brief returns the entity of EntityID id
         *
         * @param id the UUID of the entity
         * @return Entity
         */
        Entity getEntity(const EntityID& id);

        /**
         * @brief Returns the corresponding pool, correctly casted
         *
         * @tparam T 
         * @return Pool<T>*
         */
        template<typename T>
        Pool<T>* getPool() const
        {
            return dynamic_cast<Pool<T>*>(mPools.find(typeid(T).hash_code())->second);
        }

        /**
         * @brief Creates the component in place
         *
         * @param args The arguments required to build the component
         * @return ComponentHandle<T>
         */
        template<typename T, typename ...Args>
        ComponentHandle<T> push(const EntityID& id, Args... args)
        {
            auto* pool = getPool<T>();
            auto& object = pool->push(id, args...);
            return ComponentHandle<T>(&object, id, pool);
        }

        /**
         * @brief Returns the requested Component
         *
         * @tparam T 
         * @param id
         * @return Handle<T>
         */
        template<typename T>
        ComponentHandle<T> get(const EntityID& id) const
        {

            Pool<T>* pool = getPool<T>();
            return ComponentHandle<T>(pool->tryGet(id), id, pool);
        }

        template<typename T>
        std::unordered_map<EntityID, T>& components()
        {
            return getPool<T>()->components();
        }

        bool isEntityValid(const EntityID id) const
        {
            return mEntities.find(id) == mEntities.end() ? false : true;
        }

    private:
        std::unordered_map<std::size_t, BasePool*> mPools;
        std::unordered_set<UUID> mEntities;
        bool mCleaned = false;
    };


    class Entity
    {
    public:
        Entity() : mRegistry(nullptr), mID() {  }
        Entity(Registry* registry, const EntityID& id) : mRegistry(registry), mID(id) {  }
        Entity(const Entity& other) : mRegistry(other.mRegistry), mID(other.mID) {  }

        template<typename T, typename ...Args>
        ComponentHandle<T> push(Args... args)
        {
            return mRegistry->push<T>(mID, args...);
        }

        template<typename T>
        ComponentHandle<T> get() const
        {
            return mRegistry->get<T>(mID);
        }

        bool isValid() const
        {
            return mRegistry->isEntityValid(mID);
        }

        const EntityID& getID() const
        {
            return mID;
        }

    private:
        Registry* mRegistry;
        EntityID mID;
    };


    // IMPLEMENTATIONS

    template<typename T> bool ComponentHandle<T>::isValid() const
    {
        if (mPool->tryGet(mEntityID) != nullptr)
            return true;
        else
            return false;
    }
}

