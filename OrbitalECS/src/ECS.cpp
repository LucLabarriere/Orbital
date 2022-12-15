#include "OrbitalECS/ECS.h"
#include <stdexcept>

namespace Orbital
{
	namespace ECS
	{
		BaseEntity Registry::createEntity()
		{
			BaseEntity e(this, *mEntities.emplace().first);

			return e;
		}

		void Registry::deleteEntity(const EntityID& id)
		{
			auto entity = mEntities.find(id);
			Orbital::Assert(entity != mEntities.end(), "the entity does not exist");

			for (auto& [typeId, pool] : mPools)
			{
				pool->tryRemove(id);
			}

			mEntities.erase(id);
		}

		BaseEntity Registry::getEntity(const EntityID& id)
		{
			auto entity = mEntities.find(id);
			return BaseEntity(this, *entity);
		}
	} // namespace ECS
} // namespace Orbital
