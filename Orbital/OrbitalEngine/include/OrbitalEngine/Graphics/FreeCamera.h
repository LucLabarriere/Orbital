#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Graphics/CameraBehavior.h"

namespace Orbital
{
	/**
	 * @class FreeCamera
	 * @brief
	 * @todo
	 */
	class OENGINE_API FreeCamera : public CameraBehavior
	{
	public:
		/**
		 * @brief Constructor
		 *
		 * @param transform
		 */
		FreeCamera(const TransformHandle& transform);

		/**
		 * @brief Destructor
		 */
		virtual ~FreeCamera(){};

	protected:
		virtual void updateView() override;
	};
}
