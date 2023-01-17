#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/ECS/Components/CameraComponent.h"
#include "OrbitalEngine/Graphics/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Graphics/MeshRenderers/SphereRenderer.h"
#include "OrbitalEngine/Statistics.h"

namespace Orbital
{
	HighRenderer::HighRenderer(const SharedApplication& app) : HighRendererServices(app), mLowRenderer()
	{
		LOGFUNC();
	}

	HighRenderer::~HighRenderer()
	{
	}

	void HighRenderer::initialize(unsigned int windowWidth, unsigned int windowHeight)
	{
		LOGFUNC();
		mLowRenderer.initialize(windowWidth, windowHeight);

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

	void HighRenderer::draw(const MeshComponent& mc)
	{
		auto renderer = mc.getRenderer().lock();
		renderer->readyRender(mc);
		mLowRenderer.render(*renderer->getVao(), *renderer->getIbo());
	}

	void HighRenderer::onUpdate()
	{
		if (!mCamera.isValid())
		{
			Logger::Critical("The camera was not set in the Renderer");
			Logger::Critical("Instead, the camera should be set using Renderer.SetMainCamera");
			Logger::Critical("The cameras are set using Scenes.SetMainCamera which is incorrect");
			return;
		}

		mLowRenderer.resetDrawCalls();

#ifdef OENGINE_DEBUG
		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->checkShaderChanged();
		}
#endif

		for (auto& [type, renderer] : mMeshRenderers)
			mCamera->bind(renderer->getShaderProgram());

		for (auto it = mMeshComponents.rbegin(); it != mMeshComponents.rend(); it++)
		{
			draw(*it->second);
		}
		Statistics.Get<unsigned int>(Statistic::DrawCalls) = mLowRenderer.getDrawCalls();
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
		Orbital::Raise("Not implemented. TODO : unregister then register everything");
		//size_t formerPosition = mMeshVectorPositions[id];
		//size_t otherId = mMeshComponents[position].getEntityID();

		//std::swap(mMeshComponents[formerPosition], mMeshComponents[position]);
	}

	void HighRenderer::setCamera(const CameraHandle& camera)
	{
		mCamera = camera;
	}
} // namespace Orbital
