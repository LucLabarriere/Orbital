#include "OrbitalRenderer/LowRenderer.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/RendererContext.h" // TODO REMOVE
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/Maths.h"

namespace Orbital
{
	auto LowRenderer::initialize(unsigned int windowWidth, unsigned int windowHeight)
		-> Option<Error>
	{
		{
			auto error = RenderAPI::Initialize();
			if (error) return error.value();
		}

		auto result = Window::Create(windowWidth, windowHeight);
		if (!result) return result.error();
		mWindow = std::move(result.value());

		{
			auto error = RenderAPI::LateInitialize();
			if (error) return error.value();
		}

		return {};
	}

	void LowRenderer::render(const VertexArray& vao, const IndexBuffer& ibo)
	{
		vao.bind();
		ibo.bind();
		RenderAPI::DrawTriangles(0, ibo.getIndexCount());
		mDrawCalls += 1;
	}

	void LowRenderer::terminate()
	{
		RenderAPI::Terminate();
		Logger::Trace("Deleting window...");
		mWindow = nullptr;
		Logger::Trace("Deleted window");
	}

	auto LowRenderer::getWindow() -> UniqueHandle<Window>
	{
		return { &mWindow };
	}
	auto LowRenderer::getDrawCalls() const -> unsigned int
	{
		return mDrawCalls;
	}
} // namespace Orbital
