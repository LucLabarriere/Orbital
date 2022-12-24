#pragma once

#include "OrbitalEngine/ECS/Handle.h"

namespace Orbital
{
	namespace Physics
	{
		class Transform;
	}
	using TransformComponent = Physics::Transform;
	using TransformHandle = SafeHandle<TransformComponent>;

	/**
	 * @class CameraBehavior
	 * @brief Base class for LockedCamera and FreeCamera
	 *
	 */
	class CameraBehavior
	{
	public:
		/**
		 * @brief CameraBehavior type
		 *
		 * Free is a camera that is defined by a forward direction vector.
		 * Locked allways looks at a target position
		 */
		enum class Type
		{
			Free = 0,
			Locked
		};

		/**
		 * @brief Constructor
		 *
		 * @param transform
		 * @param type
		 */
		CameraBehavior(const TransformHandle& transform, CameraBehavior::Type type);

		/**
		 * @brief Destructor
		 */
		virtual ~CameraBehavior(){};

		/**
		 * @brief The target vector to supply Maths::LookAt with
		 */
		virtual Maths::Vec3 getTargetVector() const = 0;

		/**
		 * @brief Returns the TransformHandle
		 *
		 * @return [transform]
		 */
		const TransformHandle& getTransform() const;

		/**
		 * @brief Returns the position of the camera
		 *
		 * @return [transform->position]
		 */
		const Maths::Vec3& getPosition() const;

		/**
		 * @brief CameraBehavior type
		 *
		 * @return [type]
		 */
		const CameraBehavior::Type getType() const
		{
			return mType;
		}

		/**
		 * @brief Returns the LookAt matrix
		 *
		 * @return [matrix]
		 */
		Maths::Mat4 getLookAtMatrix() const;

		/**
		 * @brief Sets the main vector of the camera
		 *
		 * The main vector is the target position in the case of a LockedCamera
		 * and the forward vector in the case of a FreeCamera
		 *
		 * @param vector
		 */
		void setMainVector(const Maths::Vec3& vector)
		{
			mVector = vector;
		}

		/**
		 * @brief Sets the up vector direction
		 *
		 * @param vector [The up direction]
		 */
		void setUpVector(const Maths::Vec3& vector)
		{
			mUp = vector;
		}

	protected:
		Maths::Vec3 mVector = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 mUp = { 0.0f, 1.0f, 0.0f };
		TransformHandle mTransform;
		CameraBehavior::Type mType;
	};

	/**
	 * @class LockedCamera
	 * @brief Defined by a target position
	 *
	 */
	class LockedCamera : public CameraBehavior
	{
	public:
		/**
		 * @brief Constructor
		 *
		 * @param transform
		 */
		LockedCamera(const TransformHandle& transform);

		/**
		 * @brief Destructor
		 */
		~LockedCamera(){};

		/**
		 * @brief Returns the target position
		 *
		 * @return [target]
		 */
		virtual Maths::Vec3 getTargetVector() const override;
	};

	/**
	 * @class FreeCamera
	 * @brief Defined by a forward vector
	 *
	 */
	class FreeCamera : public CameraBehavior
	{
	public:
		FreeCamera(const TransformHandle& transform);

		/**
		 * @brief Destructor
		 */
		virtual ~FreeCamera(){};

		/**
		 * @brief Returns the forward direction
		 *
		 * @return [direction]
		 */
		virtual Maths::Vec3 getTargetVector() const override;
	};

	/**
	 * @class CameraProjection
	 * @brief Type of projection (Orthographic or Perspective)
	 *
	 */
	class CameraProjection
	{
	public:
		enum class Type
		{
			Orthographic = 0,
			Perspective
		};

		/**
		* @brief Constructor
		 *
		 * @param type [projection type]
		 */
		CameraProjection(CameraProjection::Type type) : mType(type){};

		/**
		 * @brief Destructor
		 */
		virtual ~CameraProjection(){};

		/**
		 * @brief Returns the projection matrix
		 */
		virtual Maths::Mat4 getMatrix() const = 0;

	protected:
		CameraProjection::Type mType;
	};

	/**
	 * @class OrthographicProjection
	 * @brief Orthographic projection
	 *
	 */
	class OrthographicProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		OrthographicProjection();

		/**
		 * @brief Destructor
		 */
		virtual ~OrthographicProjection(){};


		/**
		 * @brief Returns the projection matrix
		 */
		virtual Maths::Mat4 getMatrix() const override;
	};

	/**
	 * @class PerspectiveProjection
	 * @brief Perspective projection
	 *
	 */
	class PerspectiveProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		PerspectiveProjection();

		/**
		 * @brief Destructor
		 */
		virtual ~PerspectiveProjection(){};

		/**
		 * @brief Returns the projection matrix
		 */
		virtual Maths::Mat4 getMatrix() const override;
	};
} // namespace Orbital
