#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class Scene;

	class OENGINE_API ECSInterface : public ServiceInterface
	{
	public:
		ECSInterface(const SharedApplication& app);
		void Initialize();

		void Reset();
		[[nodiscard]] Entity CreateEntity();
		Entity GetEntity(const ECS::EntityID& entityID);

		template <typename T>
		void RegisterComponentType()
		{
			LOGFUNC();
			(*mRegistry)->registerComponentType<T>();
		}

		template <typename T>
		std::unordered_map<ECS::EntityID, T>& Components()
		{
			return (*mRegistry)->components<T>();
		}

		template <typename T>
		const std::unordered_map<ECS::EntityID, T>& Components() const
		{
			return (*mRegistry)->components<T>();
		}

	private:
		Scene** mScene;
		ECS::Registry** mRegistry;
	};

	OCREATE_SERVICE(ECS);
} // namespace Orbital
