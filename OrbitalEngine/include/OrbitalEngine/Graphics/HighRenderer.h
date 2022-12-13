#pragma once

#include "OrbitalEngine/Context.h"

//#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/ECS/Components/MeshFilter.h"
#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"

#include "OrbitalRenderer/LowRenderer.h"

namespace Orbital
{
	class VertexContainer;
	class BaseRenderer;
	class SphereRenderer;
	class MeshComponent;
	class MeshFilter;
	using MeshComponentHandle = SafeHandle<MeshComponent>;
	using MeshFilterHandle = SafeHandle<MeshFilter>;
	using TransformHandle = SafeHandle<TransformComponent>;

	using HighRendererServices = Services<AccessECS>;

	class OENGINE_API HighRenderer : public HighRendererServices
	{
	public:
		HighRenderer(const SharedApplication& app);
		virtual ~HighRenderer();

		void initialize();
		void terminate();

		void draw(const MeshComponent& mc) const;
		void onUpdate() const;
		WeakRef<VirtualRenderer> getRenderer(MeshType meshType)
		{
			WeakRef<VirtualRenderer> renderer;

			if (meshType == MeshType::Sphere)
			{
				return mMeshRenderers.at(MeshRendererType::Sphere);
			}
			else // Triangle, Quad, Cube
			{
				return mMeshRenderers.at(MeshRendererType::Base);
			}
		}

		Window& getWindow()
		{
			return mLowRenderer.getWindow();
		}
		// TODO Add an overload that can use Collider to initialize a meshComponent
		// TODO Rename MeshComponent to RenderComponent

	private:
		LowRenderer mLowRenderer;

		std::unordered_map<MeshRendererType, Ref<VirtualRenderer>> mMeshRenderers;
	};
} // namespace Orbital
