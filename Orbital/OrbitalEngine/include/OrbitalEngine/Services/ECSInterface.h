#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/ECS/ECSManager.h"

namespace Orbital
{
	class OENGINE_API ECSInterface : public ServiceInterface
	{
	public:
		ECSInterface();
		ECSInterface(const SharedApplication& app);
		void InitializeInterface();

		void Reset();
		[[nodiscard]] Entity CreateEntity();
		void DeleteEntity(const EntityID& id);
		void RequestDeleteEntity(const EntityID& id);
		Entity GetEntity(const EntityID& entityID);
		Ref<ECSManager>& getManager();
		const Ref<ECSManager>& getManager() const;


		template <typename T>
		void RegisterComponentType()
		{
			getManager()->registerComponentType<T>();
		}

		template <typename T>
		ECS::ComponentContainer<T>& Components()
		{
			return getManager()->components<T>();
		}

		template <typename T>
		const ECS::ComponentContainer<T>& Components() const
		{
			return getManager()->components<T>();
		}

	private:
		Unique<Scene>* mScene;
	};

	OCREATE_SERVICE(ECS);
} // namespace Orbital
