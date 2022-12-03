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
			assert(entity != mEntities.end());

			for (auto& [typeId, pool] : mPools)
			{
				pool->tryRemove(id);
			}

			mEntities.erase(id);
		}

		BaseEntity Registry::getEntity(const EntityID& id)
		{
			auto entity = mEntities.find(id);
			assert(entity != mEntities.end());
			return BaseEntity(this, *entity);
		}
	} // namespace ECS
} // namespace Orbital
