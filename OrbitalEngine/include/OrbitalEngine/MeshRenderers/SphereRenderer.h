#pragma once

#include "OrbitalEngine/MeshRenderers/VirtualRenderer.h"

namespace Orbital
{
	class OENGINE_API SphereRenderer : public VirtualRenderer 
	{
	public:
		SphereRenderer() : VirtualRenderer()
		{
		}

		virtual ~SphereRenderer() override
		{
		}

		virtual void initialize() override;
		virtual void terminate() override;
		virtual void readyRender(const MeshComponent& mc) const override;
	};
} // namespace Orbital
