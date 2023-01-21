#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Graphics/CameraBehavior.h"

namespace Orbital
{
	/**
	 * @class LockedCamera
	 * @brief 
	 * @todo Fill
	 */
	class ORBITAL_ENGINE_API LockedCamera : public CameraBehavior
	{
	public:
		/**
		 * @brief Constructor
		 *
		 * @param transform
		 */
		LockedCamera(const SharedApplication& app, const TransformHandle& transform);

		/**
		 * @brief Destructor
		 */
		~LockedCamera(){};

	protected:
		virtual void updateView() override;
	};
}
