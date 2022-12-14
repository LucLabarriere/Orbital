#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Graphics/MeshRenderers/SphereRenderer.h"

namespace Orbital
{
	HighRenderer::HighRenderer(const SharedApplication& app) : HighRendererServices(app), mLowRenderer()
	{
	}

	HighRenderer::~HighRenderer()
	{
	}

	void HighRenderer::initialize()
	{
		mLowRenderer.initialize();

		mMeshRenderers.emplace(MeshRendererType::Base, new BaseRenderer);
		mMeshRenderers.emplace(MeshRendererType::Sphere, new SphereRenderer);

		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->initialize();
		}
	}

	void HighRenderer::terminate()
	{
		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->terminate();
		}

		mLowRenderer.terminate();
	}

	void HighRenderer::draw(const MeshComponent& mc) const
	{
		auto renderer = mc.getRenderer().lock();
		renderer->readyRender(mc);
		mLowRenderer.render(*renderer->getVao(), *renderer->getIbo());
	}

	void HighRenderer::onUpdate() const
	{
#ifdef ODEBUG
		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->checkShaderChanged();
		}
#endif

		for (auto it = mMeshComponents.rbegin(); it != mMeshComponents.rend(); it++)
		{
			draw(*it->second);
		}
	}

	void HighRenderer::registerMeshComponent(const MeshComponentHandle& meshComponent)
	{
		mMeshComponents.emplace(meshComponent.getEntityID(), meshComponent);
	}

	void HighRenderer::unregisterMeshComponent(const EntityID& id)
	{
		mMeshComponents.erase(id);
	}

	void HighRenderer::clearComponents()
	{
		mMeshComponents.clear();
	}

	void HighRenderer::setRenderOrder(const EntityID& id, size_t position)
	{
		Orbital::Assert(false, "Not implemented. TODO : unregister then register everything");
		//size_t formerPosition = mMeshVectorPositions[id];
		//size_t otherId = mMeshComponents[position].getEntityID();

		//std::swap(mMeshComponents[formerPosition], mMeshComponents[position]);
	}
} // namespace Orbital
