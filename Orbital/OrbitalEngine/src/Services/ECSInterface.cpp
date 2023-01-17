#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/Scene.h"

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

	Entity ECSInterface::CreateEntity()
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

	Entity ECSInterface::GetEntity(const ECS::EntityID& entityID)
	{
		return getManager()->getEntity(entityID);
	}

	Ref<ECSManager>& ECSInterface::getManager()
	{
		return *mScene->get()->getManager();
	}

	const Ref<ECSManager>& ECSInterface::getManager() const
	{
		return *mScene->get()->getManager();
	}
} // namespace Orbital
