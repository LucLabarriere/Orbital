#pragma once
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Graphics/Camera.h"

namespace Orbital
{
	struct CameraSpecs
	{
		CameraBehavior::Type behavior = CameraBehavior::Type::Free;
		CameraProjection::Type projection = CameraProjection::Type::Perspective;

		Maths::Vec3 up = { 0.0f, 1.0f, 0.0f };
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
		CameraComponent(const Component::InitArgs& args, const TransformHandle& transform, const CameraSpecs& specs);

		/**
		 * @brief Sends the View matrix to the GPU
		 *
		 * @param program [The Shader program]
		 */
		void bind(const ShaderProgram& program) const;

		/**
		 * @brief The view matrix constructed in place
		 */
		Maths::Mat4 getViewMatrix() const;

		/**
		 * @brief MainVector of the camera
		 *
		 * Target position in the case of a LockedCamera
		 * Direction vector in the case of a FreeCamera
		 *
		 * @param vector
		 */
		void setMainVector(const Maths::Vec3& vector)
		{
			mBehavior->setMainVector(vector);
		}

		/**
		 * @brief Up direction of the camera
		 *
		 * Usually, the up vector is usually :
		 * 		{ 0.0f, 1.0f, 0.0f }
		 *
		 * @param up [Up direction vector]
		 */
		void setUpVector(const Maths::Vec3& up)
		{
			mBehavior->setUpVector(up);
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
