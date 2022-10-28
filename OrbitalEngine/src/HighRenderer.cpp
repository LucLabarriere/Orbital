#include "OrbitalEngine/HighRenderer.h"
#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/MeshRenderers/SphereRenderer.h"
#include "OrbitalEngine/VertexContainer.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalTools/Maths.h"

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
		auto renderer = mc.getRenderer();
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

	MeshComponentHandle HighRenderer::pushMeshComponent(Entity& e, MeshType meshType, const TransformHandle& transform)
	{
		if (meshType == MeshType::Sphere)
		{
			return e.push<MeshComponent>(meshType, transform, mMeshRenderers.at(MeshRendererType::Sphere));
		}
		else // Triangle, Quad, Cube
		{
			return e.push<MeshComponent>(meshType, transform, mMeshRenderers.at(MeshRendererType::Base));
		}
	}
} // namespace Orbital
