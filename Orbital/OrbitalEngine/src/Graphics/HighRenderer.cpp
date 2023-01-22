#include "OrbitalEngine/Graphics/HighRenderer.h"
#include "OrbitalEngine/ECS/Components/CameraComponent.h"
#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/MeshRenderers/BaseRenderer.h"
#include "OrbitalEngine/Graphics/MeshRenderers/SphereRenderer.h"
#include "OrbitalEngine/Statistics.h"

namespace Orbital
{
	HighRenderer::HighRenderer(const SharedApplication& app)
		: HighRendererServices(app), mLowRenderer()
	{
	}

	auto HighRenderer::initialize(unsigned int windowWidth, unsigned int windowHeight)
		-> Option<Error>
	{
		auto error = mLowRenderer.initialize(windowWidth, windowHeight);

		if (error) return error;

		mMeshRenderers.emplace(MeshRendererType::Base, new BaseRenderer);
		mMeshRenderers.emplace(MeshRendererType::Sphere, new SphereRenderer);

		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->initialize();
		}

		return {};
	}

	auto HighRenderer::terminate() -> void
	{
		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->terminate();
		}

		mLowRenderer.terminate();
	}

	auto HighRenderer::draw(const MeshComponent& mc) -> void
	{
		auto renderer = mc.getRenderer().lock();
		renderer->readyRender(mc);

		mLowRenderer.render(*renderer->getVao(), *renderer->getIbo());
	}

	auto HighRenderer::bindCamera() -> void
	{
		for (auto& [type, renderer] : mMeshRenderers)
			mCamera->bind(renderer->getShaderProgram());
	}

	auto HighRenderer::onUpdate() -> void
	{
		if (!mCamera.isValid())
		{
			Logger::Critical("The camera was not set in the Renderer");
			Logger::Critical(
				"Instead, the camera should be set using Renderer.SetMainCamera"
			);
			Logger::Critical(
				"The cameras are set using Scenes.SetMainCamera which is incorrect"
			);
			return;
		}

		mLowRenderer.resetDrawCalls();

#ifdef ORBITAL_DEV
		for (auto& [rendererType, renderer] : mMeshRenderers)
		{
			renderer->checkShaderChanged();
		}
#endif

		// for (auto& [type, renderer] : mMeshRenderers)
		//	mCamera->bind(renderer->getShaderProgram());

		// for (auto it = mMeshComponents.rbegin(); it != mMeshComponents.rend(); it++)
		//{
		//	draw(*it->second);
		// }
		Statistics.Get<unsigned int>(Statistic::DrawCalls) = mLowRenderer.getDrawCalls();
	}

	auto HighRenderer::registerMeshComponent(const MeshComponentHandle& meshComponent)
		-> void
	{
		mMeshComponents.emplace(meshComponent.getEntityID(), meshComponent);
	}

	auto HighRenderer::unregisterMeshComponent(const EntityID& id) -> void
	{
		mMeshComponents.erase(id);
	}

	auto HighRenderer::clearComponents() -> void
	{
		mMeshComponents.clear();
	}

	auto HighRenderer::setRenderOrder(const EntityID& id, size_t position) -> void
	{
		Orbital::Raise("Not implemented. TODO : unregister then register everything");
		// size_t formerPosition = mMeshVectorPositions[id];
		// size_t otherId = mMeshComponents[position].getEntityID();

		// std::swap(mMeshComponents[formerPosition], mMeshComponents[position]);
	}

	void HighRenderer::setCamera(const CameraHandle& camera)
	{
		mCamera = camera;
	}

	auto HighRenderer::getWindow() -> UniqueHandle<Window>
	{
		return mLowRenderer.getWindow();
	}
} // namespace Orbital
