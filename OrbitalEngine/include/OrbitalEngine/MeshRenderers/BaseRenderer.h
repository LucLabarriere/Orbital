#pragma once

#include "OrbitalEngine/MeshRenderers/VirtualRenderer.h"

namespace Orbital
{
	class OENGINE_API BaseRenderer : public VirtualRenderer
	{
	public:
		BaseRenderer() : VirtualRenderer()
		{
		}

		virtual ~BaseRenderer() override
		{
		}

		virtual void initialize() override;
		virtual void terminate() override;
		virtual void readyRender(const MeshComponent& mc) const override;
	};
} // namespace Orbital
