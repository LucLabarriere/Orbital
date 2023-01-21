#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	/**
	 * @class VertexContainer
	 * @brief VertexArray, VertexBuffer and IndexBuffer
	 *
	 * @todo Verify here that the raw pointers are necessary
	 */
	class ORBITAL_ENGINE_API VertexContainer
	{
	public:
		virtual ~VertexContainer();

		/**
		 * @brief Get the Vertex Array object
		 *
		 * @return Ras pointer to the allocated memory
		 */
		VertexArray* getVao();

		/**
		 * @brief Get the Index Buffer object
		 *
		 * @return Raw pointer to the allocated memory
		 */
		IndexBuffer* getIbo();

		inline size_t getVertexCount() const
		{
			return mVertexCount;
		};

		/**
		 * @brief VertexContainer corresponding to a triangle
		 *
		 * @return Raw pointer to the allocated memory
		 */
		static VertexContainer* Triangle();

		/**
		 * @brief VertexContainer corresponding to a Quand
		 *
		 * @return Raw pointer to the allocated memory
		 */
		static VertexContainer* Quad();

		/**
		 * @brief VertexContainer corresponding to a Cube
		 *
		 * @todo Implement
		 *
		 * @return Raw pointer to the allocated memory
		 */
		static VertexContainer* Cube();

	private:
		VertexContainer(VertexArray* vao, IndexBuffer* ibo, VertexBuffer* vbo, size_t vertexCount);

	private:
		VertexArray* mVAO = nullptr;
		IndexBuffer* mIBO = nullptr;
		VertexBuffer* mVBO = nullptr;
		size_t mVertexCount = 0;
	};
} // namespace Orbital
