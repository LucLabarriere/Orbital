#include "OrbitalEngine/ECS/Components/CameraComponent.h"
#include "OrbitalEngine/Graphics/HighRenderer.h"

#include "OrbitalEngine/Graphics/FreeCamera.h"
#include "OrbitalEngine/Graphics/LockedCamera.h"

#include "OrbitalEngine/Graphics/OrthographicProjection.h"
#include "OrbitalEngine/Graphics/PerspectiveProjection.h"

namespace Orbital
{
	CameraComponent::CameraComponent(
		const Component::InitArgs& args, const SharedApplication& app,
		const TransformHandle& transform, const CameraSpecs& specs
	)
		: Component(args)
	{
		switch (specs.behavior)
		{
		case CameraBehavior::Type::Free:
		{
			mBehavior = MakeUnique<FreeCamera>(app, transform);
			break;
		}
		case CameraBehavior::Type::Locked:
		{
			mBehavior = MakeUnique<LockedCamera>(app, transform);
			break;
		}
		}

		switch (specs.projection)
		{
		case CameraProjection::Type::Orthographic:
		{
			mProjection = MakeUnique<OrthographicProjection>(app);
			break;
		}
		case CameraProjection::Type::Perspective:
		{
			mProjection = MakeUnique<PerspectiveProjection>(app);
			break;
		}
		}
	}

	void CameraComponent::bind(const ShaderProgram& program) const
	{
		program.bind();
		Maths::Mat4 view = getViewMatrix();
		program.setUniform<Maths::Mat4>(Uniform::View, view);
	}

	template <>
	auto Entity::push<CameraComponent>(CameraSpecs&& specs) -> SafeHandle<CameraComponent>
	{
		Orbital::Assert(
			!get<CameraComponent>().isValid(),
			"Entity already has the requested component"
		);
		ECS::Registry* registry = mManager.lock()->getRegistry();

		auto transform = registry->get<TransformComponent>(mEntityID);

		if (!transform.isValid())
		{
			transform = registry->push<TransformComponent>(mEntityID);
		}

		registry->push<CameraComponent>(
			mEntityID, getComponentArgs(), mApp, get<TransformComponent>(), specs
		);

		return SafeHandle<CameraComponent>(mEntityID, mManager);
	}
} // namespace Orbital
