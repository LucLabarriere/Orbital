#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/Graphics/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Graphics/MeshRenderers/SphereRenderer.h"
#include "OrbitalEngine/ECS/Components/MeshComponent.h"

namespace Orbital
{
	HighRenderer::HighRenderer(const SharedApplication& app) : HighRendererServices(app), mLowRenderer()
	{
		LOGFUNC();
	}

	HighRenderer::~HighRenderer()
	{
		LOGFUNC();
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

		Logger::Trace("Done initializing High renderer");
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

		for (const auto& [uuid, mc] : ECS.Components<MeshComponent>())
		{
			draw(mc);
		}
	}
} // namespace Orbital
