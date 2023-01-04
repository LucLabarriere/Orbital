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
	 *
	 */
	class OENGINE_API CameraComponent : public Component
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
		void bind(const ShaderProgram& program) const;

		inline Maths::Mat4 getViewMatrix() const
		{
			return mProjection->getMatrix() * mBehavior->getViewMatrix();
		}

		inline const Maths::Vec3& getUp() const
		{
			return mBehavior->getUp();
		}

		inline const Maths::Vec3& getRight() const
		{
			return mBehavior->getRight();
		}

		inline const Maths::Vec3& getFront() const
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
	OENGINE_API SafeHandle<CameraComponent> Entity::push<CameraComponent>(CameraSpecs&& specs);
} // namespace Orbital
