#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class Scene;
	class Collider;

	class OENGINE_API ECSInterface : public ServiceInterface
	{
	public:
		ECSInterface(const SharedApplication& app);
		void Initialize();

		void Reset();
		[[nodiscard]] Entity CreateEntity();
		Entity GetEntity(const EntityID& entityID);

		template <typename T>
		void RegisterComponentType()
		{
			LOGFUNC();

			if constexpr (std::is_base_of<Collider, T>::value)
			{
				(*mRegistry)->registerDerivableComponentType<T>();
			}
			else
			{
				(*mRegistry)->registerComponentType<T>();
			}
		}

		template <typename T>
		std::unordered_map<EntityID, T>& Components()
		{
			return (*mRegistry)->components<T>();
		}

		template <typename T>
		std::unordered_map<EntityID, T*>& DerivedComponents()
		{
			return (*mRegistry)->derivedComponents<T>();
		}

		template <typename T>
		const std::unordered_map<EntityID, T>& Components() const
		{
			return (*mRegistry)->components<T>();
		}

		template <typename T>
		const std::unordered_map<EntityID, T*>& DerivedComponents() const
		{
			return (*mRegistry)->derivedComponents<T>();
		}

	private:
		Scene** mScene;
		Registry** mRegistry;
	};

	OCREATE_SERVICE(ECS);
} // namespace Orbital
