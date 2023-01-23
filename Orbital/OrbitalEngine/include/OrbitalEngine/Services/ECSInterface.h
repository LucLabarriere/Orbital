#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API ECSInterface : public ServiceInterface
	{
	public:
		ECSInterface();
		ECSInterface(const SharedApplication& app);
		void InitializeInterface();

		void Reset();
		[[nodiscard]] auto CreateEntity() -> Entity;
		void DeleteEntity(const EntityID& id);
		void RequestDeleteEntity(const EntityID& id);
		auto GetEntity(const EntityID& entityID) -> Entity;
		auto getManager() -> Ref<ECSManager>&;
		auto getManager() const -> const Ref<ECSManager>&;

		template <typename T>
		void RegisterComponentType()
		{
			getManager()->registerComponentType<T>();
		}

		template <typename T>
		auto Components() -> ECS::ComponentContainer<T>&
		{
			return getManager()->components<T>();
		}

		template <typename T>
		auto Components() const -> const ECS::ComponentContainer<T>&
		{
			return getManager()->components<T>();
		}

	private:
		Unique<Scene>* mScene;
	};

	OCREATE_SERVICE(ECS);
} // namespace Orbital
