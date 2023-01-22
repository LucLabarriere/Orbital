#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
	ECSInterface::ECSInterface() : ServiceInterface()
	{
	}

	ECSInterface::ECSInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void ECSInterface::InitializeInterface()
	{
		mScene = mApp.lock()->getSceneManager().lock()->getCurrentScene();
	}

	void ECSInterface::Reset()
	{
		getManager()->reset();
	}

	auto ECSInterface::CreateEntity() -> Entity
	{
		return mScene->get()->createEntity();
	}

	void ECSInterface::DeleteEntity(const EntityID& id)
	{
		mScene->get()->deleteEntity(id);
	}

	void ECSInterface::RequestDeleteEntity(const EntityID& id)
	{
		mScene->get()->requestDeleteEntity(id);
	}

	auto ECSInterface::GetEntity(const ECS::EntityID& entityID) -> Entity
	{
		return getManager()->getEntity(entityID);
	}

	auto ECSInterface::getManager() -> Ref<ECSManager>&
	{
		return *mScene->get()->getManager();
	}

	auto ECSInterface::getManager() const -> const Ref<ECSManager>&
	{
		return *mScene->get()->getManager();
	}
} // namespace Orbital
