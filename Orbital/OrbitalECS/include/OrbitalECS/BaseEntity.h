#ifndef OECS_INCLUDED
// Make sure the ECS headers are loaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OBASEENTITY_INCLUDED
#define OBASEENTITY_INCLUDED

namespace Orbital::ECS
{
	class BaseEntity
	{
	public:
		BaseEntity() : mRegistry(nullptr), mID(){};
		BaseEntity(Registry* registry, const EntityID& id)
			: mRegistry(registry), mID(id){};
		BaseEntity(const BaseEntity& other) = default;

		template <typename T, typename... Args>
		auto push(Args... args) -> Handle<T>
		{
			return mRegistry->push<T>(mID, args...);
		}

		template <typename T>
		auto get() const -> const Handle<T>
		{
			return mRegistry->get<T>(mID);
		}

		template <typename T>
		auto get() -> Handle<T>
		{
			return mRegistry->get<T>(mID);
		}

		template <typename T>
		void remove()
		{
			mRegistry->remove<T>(mID);
		}

		void destroy() { mRegistry->deleteEntity(mID); }

		[[nodiscard]] auto isValid() const -> bool
		{
			return mRegistry->isEntityValid(mID);
		}

		[[nodiscard]] auto getID() const -> const EntityID& { return mID; }

		[[nodiscard]] auto getRegistry() const -> Registry* { return mRegistry; }

	private:
		Registry* mRegistry;
		EntityID mID;
	};
} // namespace Orbital::ECS
#endif
