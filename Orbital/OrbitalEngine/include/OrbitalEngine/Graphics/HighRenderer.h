#pragma once

#include "OrbitalEngine/Context.h"

//#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/ECS/Components/MeshFilter.h"
#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"

#include "OrbitalRenderer/LowRenderer.h"

namespace Orbital
{
	// Forward declarations
	class VertexContainer;
	class BaseRenderer;
	class SphereRenderer;
	class MeshComponent;
	class CameraComponent;
	class MeshFilter;
	using MeshComponentHandle = SafeHandle<MeshComponent>;
	using MeshFilterHandle = SafeHandle<MeshFilter>;
	using CameraHandle = SafeHandle<CameraComponent>;
	using HighRendererServices = Services<AccessECS>;
	//

	/**
	 * @class HighRenderer 
	 * @brief High level renderer class
	 *
	 * @todo Add an overload that can use Collider to initialize a meshComponent
	 * @todo Rename MeshComponent to RenderComponent
	 */
	class OENGINE_API HighRenderer : public HighRendererServices
	{
	public:
		HighRenderer(const SharedApplication& app);
		HighRenderer(const HighRenderer&) = delete;
		HighRenderer(HighRenderer&&) = delete;
		virtual ~HighRenderer();

		void initialize(unsigned int windowWidth, unsigned int windowHeight);
		void terminate();

		void draw(const MeshComponent& mc) const;
		void onUpdate() const;

		/**
		 * @brief Get the renderer of the given MeshType
		 *
		 * @todo Move to the cpp file
		 *
		 * @param meshType 
		 */
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

		void registerMeshComponent(const MeshComponentHandle& meshComponent);
		void unregisterMeshComponent(const EntityID& id);
		void clearComponents();
		void clearComponents(const EntityID& id);
		void setRenderOrder(const EntityID& id, size_t position);
		void setCamera(const CameraHandle& camera);

		Window& getWindow()
		{
			return mLowRenderer.getWindow();
		}

	private:
		LowRenderer mLowRenderer;

		CameraHandle mCamera;
		std::map<MeshRendererType, Ref<VirtualRenderer>> mMeshRenderers;
		std::map<EntityID, MeshComponentHandle> mMeshComponents;
	};
} // namespace Orbital
