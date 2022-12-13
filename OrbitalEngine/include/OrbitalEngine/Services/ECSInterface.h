#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	class Scene;

	class OENGINE_API ECSInterface : public ServiceInterface
	{
	public:
		ECSInterface();
		ECSInterface(const SharedApplication& app);
		void Initialize();

		void Reset();
		[[nodiscard]] Entity CreateEntity();
		void DeleteEntity(const EntityID& id);
		Entity GetEntity(const ECS::EntityID& entityID);

		template <typename T>
		void RegisterComponentType()
		{
			mManager.lock()->registerComponentType<T>();
		}

		template <typename T>
		std::unordered_map<ECS::EntityID, T>& Components()
		{
			return mManager.lock()->components<T>();
		}

		template <typename T>
		const std::unordered_map<ECS::EntityID, T>& Components() const
		{
			return mManager.lock()->components<T>();
		}

	private:
		WeakRef<Scene> mScene;
		WeakRef<ECSManager> mManager;
	};

	OCREATE_SERVICE(ECS);
} // namespace Orbital
