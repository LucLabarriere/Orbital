#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalEngine/Services/SettingsInterface.h"

namespace Orbital
{
	using CameraServices = Services<AccessSettings>;

	/**
	 * @class CameraBehavior
	 * @brief Base class for LockedCamera and FreeCamera
	 *
	 */
	class ORBITAL_ENGINE_API CameraBehavior : public CameraServices
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
		CameraBehavior(const SharedApplication& app, const TransformHandle& transform, CameraBehavior::Type type);

		/**
		 * @brief Destructor
		 */
		virtual ~CameraBehavior(){};

		void lookAt(const Maths::Vec3& target);

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
		inline CameraBehavior::Type getType() const
		{
			return mType;
		}

		inline const Maths::Mat4& getViewMatrix()
		{
			updateView();
			return mView;
		}

		inline const Maths::Vec3& getUp()
		{
			updateView();
			return mUp;
		}

		inline const Maths::Vec3& getRight()
		{
			updateView();
			return mRight;
		}

		inline const Maths::Vec3& getFront()
		{
			updateView();
			return mFront;
		}
	
	protected:
		virtual void updateView() = 0;

	protected:
		Maths::Vec3 mUp = { 0.0f, 1.0f, 0.0f };
		Maths::Vec3 mRight = { 1.0f, 0.0f, 0.0f };
		Maths::Vec3 mFront = { 0.0f, 0.0f, 1.0f };
		Maths::Mat4 mView = Maths::Mat4(1.0f);

		TransformHandle mTransform;
		CameraBehavior::Type mType;
	};
}
