#include "OrbitalEngine/Graphics/VertexContainer.h"
#include "OrbitalRenderer/IndexBuffer.h"
#include "OrbitalRenderer/VertexArray.h"
#include "OrbitalRenderer/VertexBuffer.h"

namespace Orbital
{
	VertexContainer::VertexContainer(
		VertexArray* vao, IndexBuffer* ibo, VertexBuffer* vbo, size_t vertexCount
	)
		: mVAO(vao), mIBO(ibo), mVBO(vbo), mVertexCount(vertexCount)
	{
	}

	VertexContainer::~VertexContainer()
	{
		delete mVAO;
		delete mIBO;
		delete mVBO;
	}

	auto VertexContainer::getVao() -> VertexArray*
	{
		return mVAO;
	}

	auto VertexContainer::getIbo() -> IndexBuffer*
	{
		return mIBO;
	}

	auto VertexContainer::Triangle() -> VertexContainer*
	{
		float a = 1.0f / Maths::Tan(Maths::Radian(60.0f));
		float h1 = -a * Maths::Tan(Maths::Radian(30.0f));
		float h2 = 1 + h1;

		unsigned int indices[3] = { 0, 1, 2 };

		float vertices[18] = { -a,	 h1,   0.0f, 1.0f, 0.0f, 0.0f, a,	 h1,   0.0f,
							   1.0f, 0.0f, 0.0f, 0.0f, h2,	 0.0f, 1.0f, 0.0f, 0.0f };

		auto vao = VertexArray::Create();
		vao->bind();
		auto vbo = VertexBuffer::Create(sizeof(vertices), sizeof(float) * 6, vertices);
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

		auto ibo = IndexBuffer::Create(sizeof(indices), 3, indices);

		return new VertexContainer(vao, ibo, vbo, 3);
	}

	auto VertexContainer::Quad() -> VertexContainer*
	{
		unsigned int indices[6] = { 0, 1, 2, 1, 2, 3 };

		float vertices[24] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.5f, -0.5f,
							   0.0f,  1.0f,	 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 1.0f,
							   0.0f,  0.0f,	 0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f };

		auto vao = VertexArray::Create();
		vao->bind();
		auto vbo = VertexBuffer::Create(sizeof(vertices), sizeof(float) * 6, vertices);
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

		auto ibo = IndexBuffer::Create(sizeof(indices), 6, indices);

		return new VertexContainer(vao, ibo, vbo, 4);
	}

	auto VertexContainer::Cube() -> VertexContainer*
	{
		unsigned int indices[36] = {
			0,	1,	2,	1,	2,	3,	4,	5,	6,	5,	6,	7,	8,	9,	10, 9,	10, 11,
			12, 13, 14, 13, 14, 15, 16, 17, 18, 17, 18, 19, 20, 21, 22, 21, 22, 23,
		};

		float vertices[144] = {
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
			-0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 0.5f,  0.5f,	 -0.5f, 1.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, 0.5f,	 0.0f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,	0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f,  0.5f,	 0.0f, 1.0f, 1.0f, 0.5f,  0.5f,	 0.5f,	0.0f, 1.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f,	 1.0f, 1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,	1.0f, 1.0f, 0.0f,

			-0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.5f,  0.5f,	 -0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, 0.0f, 0.5f,  0.5f,	 0.5f,	1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f,	 -0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, 1.0f, -0.5f, 0.5f,	 0.5f,	0.0f, 0.0f, 1.0f,

			0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f,  0.5f,	 -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  -0.5f, 0.5f,	 0.0f, 1.0f, 0.0f, 0.5f,  0.5f,	 0.5f,	0.0f, 1.0f, 0.0f,
		};

		auto vao = VertexArray::Create();
		vao->bind();
		auto vbo = VertexBuffer::Create(sizeof(vertices), sizeof(float) * 6, vertices);
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Position
		vbo->addVertexAttribute(3, sizeof(float) * 3); // Color

		auto ibo = IndexBuffer::Create(sizeof(indices), 36, indices);

		return new VertexContainer(vao, ibo, vbo, 24);
	}
} // namespace Orbital
