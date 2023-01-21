#pragma once
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Graphics/CameraBehavior.h"
#include "OrbitalEngine/Graphics/CameraProjection.h"

namespace Orbital
{
	struct CameraSpecs
	{
		CameraBehavior::Type behavior = CameraBehavior::Type::Free;
		CameraProjection::Type projection = CameraProjection::Type::Perspective;
	};

	/**
	 * @class CameraComponent
	 * @brief Component for the ECS
	 */
	class ORBITAL_ENGINE_API CameraComponent : public Component
	{
	public:
		/**
		 * @brief Constructor
		 *
		 * @param args [Component arguments]
		 * @param transform [Transform of the Entity]
		 * @param specs [Specs of the camera]
		 */
		CameraComponent(
			const Component::InitArgs& args, const SharedApplication& app, const TransformHandle& transform,
			const CameraSpecs& specs
		);

		/**
		 * @brief Sends the View matrix to the GPU
		 *
		 * @param program [The Shader program]
		 */
		auto bind(const ShaderProgram& program) const -> void;

		auto lookAt(const Maths::Vec3& target) -> void
		{
			return mBehavior->lookAt(target);
		}

		[[nodiscard]] auto getViewMatrix() const -> Maths::Mat4
		{
			return mProjection->getMatrix() * mBehavior->getViewMatrix();
		}

		[[nodiscard]] auto getUp() const -> const Maths::Vec3&
		{
			return mBehavior->getUp();
		}

		[[nodiscard]] auto getRight() const -> const Maths::Vec3&
		{
			return mBehavior->getRight();
		}

		[[nodiscard]] auto getFront() const -> const Maths::Vec3&
		{
			return mBehavior->getFront();
		}

	protected:
		Unique<CameraBehavior> mBehavior;
		Unique<CameraProjection> mProjection;
	};

	using CameraHandle = SafeHandle<CameraComponent>;

	/**
	 * @brief Adds a CameraComponent
	 *
	 *
	 * @return SafeHandle<CameraComponent>
	 */
	template <>
	ORBITAL_ENGINE_API auto Entity::push<CameraComponent>(CameraSpecs&& specs) -> SafeHandle<CameraComponent>;
} // namespace Orbital
