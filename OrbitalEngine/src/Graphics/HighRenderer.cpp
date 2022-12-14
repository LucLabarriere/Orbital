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
		mMeshComponents.reserve(500);

		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->initialize();
		}
	}

	void HighRenderer::terminate()
	{
		LOGFUNC();
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
			draw(*(*it));
		}
	}

	void HighRenderer::registerMeshComponent(const MeshComponentHandle& meshComponent)
	{
		mMeshComponents.push_back(meshComponent);
	}

	void HighRenderer::unregisterMeshComponent(const EntityID& id)
	{
		for (auto it = mMeshComponents.begin(); it != mMeshComponents.end(); it++)
		{
			if ((*it)->getEntityID() == id)
				mMeshComponents.erase(it);
		}
	}

	void HighRenderer::clearComponents()
	{
		mMeshComponents.clear();
	}

	void HighRenderer::setRenderOrder(const EntityID& id, size_t position)
	{
		for (auto it = mMeshComponents.begin(); it != mMeshComponents.end(); it++)
		{
			if ((*it)->getEntityID() == id)
				std::swap(mMeshComponents[position], *it);
		}
	}

} // namespace Orbital
