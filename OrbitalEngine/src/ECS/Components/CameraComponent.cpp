#include "OrbitalEngine/ECS/Components/CameraComponent.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"

namespace Orbital
{
	CameraComponent::CameraComponent(
		const Component::InitArgs& args, const TransformHandle& transform, const CameraSpecs& specs
	)
		: Component(args)
	{
		switch (specs.behavior)
		{
		case CameraBehavior::Type::Free:
		{
			mBehavior = MakeUnique<FreeCamera>(transform);
			break;
		}
		case CameraBehavior::Type::Locked:
		{
			mBehavior = MakeUnique<LockedCamera>(transform);
			break;
		}
		}

		switch (specs.projection)
		{
		case CameraProjection::Type::Orthographic:
		{
			mProjection = MakeUnique<OrthographicProjection>();
			break;
		}
		case CameraProjection::Type::Perspective:
		{
			mProjection = MakeUnique<PerspectiveProjection>();
			break;
		}
		}

		mBehavior->setUpVector(specs.up);
	}

	void CameraComponent::bind(const ShaderProgram& program) const
	{
		program.bind();
		Maths::Mat4 view = getViewMatrix();
		program.setUniform<Maths::Mat4>(Uniform::View, view);
	}

	Maths::Mat4 CameraComponent::getViewMatrix() const
	{
		Maths::Mat4 view = mProjection->getMatrix() * mBehavior->getLookAtMatrix();

		return view;
	}

	template <>
	SafeHandle<CameraComponent> Entity::push<CameraComponent>(CameraSpecs&& specs)
	{
		Orbital::Assert(!get<CameraComponent>().isValid(), "Entity already has the requested component");
		ECS::Registry* registry = mManager.lock()->getRegistry();

		auto transform = registry->get<TransformComponent>(mEntityID);

		if (!transform.isValid())
		{
			transform = registry->push<TransformComponent>(mEntityID);
		}

		registry->push<CameraComponent>(mEntityID, getComponentArgs(), get<TransformComponent>(), specs);

		return SafeHandle<CameraComponent>(mEntityID, mManager);
	}
} // namespace Orbital
