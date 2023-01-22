#ifndef OECS_INCLUDED
// Make sure the ECS headers areloaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OCONTAINERS_INCLUDED
#define OCONTAINERS_INCLUDED

namespace Orbital::ECS
{
	template <typename T>
	using ComponentContainer = std::map<ECS::EntityID, T>;

	class BasePool
	{
	public:
		BasePool() = default;
		virtual ~BasePool() = default;

		virtual void clear() = 0;
		virtual void tryRemove(const EntityID& id) = 0;
	};

	template <typename T>
	class Pool : public BasePool
	{
	public:
		Pool() = default;
		~Pool() override = default;

		/**
		 * @brief Creates a component inplace and returns a reference to it
		 *
		 * @tparam Args
		 * @param id
		 * @param args
		 * @return T&
		 */
		template <typename... Args>
		auto push(const EntityID id, Args&&... args) -> T&
		{
			return mObjects.try_emplace(id, args...).first->second;
		}

		/**
		 * @brief Returns the component matching the EntityID
		 *
		 * @param id
		 * @return
		 */
		auto tryGet(const EntityID& id) -> T*
		{
			auto object = mObjects.find(id);

			if (object != mObjects.end())
				return &object->second;
			else
				return nullptr;
		}

		void remove(const EntityID id)
		{
			auto object = mObjects.find(id);
			Orbital::Assert(
				object != mObjects.end(), "The entity does not have this component"
			);
			mObjects.erase(id);
		}

		void tryRemove(const EntityID& id) override
		{
			auto object = mObjects.find(id);
			if (object != mObjects.end()) mObjects.erase(id);
		}

		void clear() override { mObjects.clear(); }

		auto components() -> ComponentContainer<T>& { return mObjects; }

	private:
		ComponentContainer<T> mObjects;
	};
} // namespace Orbital::ECS
#endif
