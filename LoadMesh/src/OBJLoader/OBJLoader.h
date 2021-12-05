#ifndef OBJLOADER_H
#define OBJLOADER_H

// Components:
#include "Position.h"
#include "TextureCoord.h"
#include "Normal.h"

// External dependancies:
#include "../RenderSystem/D3DUtility.h"
#include "../RenderSystem/Vertex.h"

namespace obj
{
	class OBJLoader
	{
	public:

	// Constructors and Destructor:

		OBJLoader();
		
		~OBJLoader();

	// Functions:

		/// <summary>
		/// Load Vertex positions, texture coordinates and normals from .obj file to the buffers.
		/// </summary>
		/// <param name="filePath"> - Full path to the .obj file.</param>
		/// <param name="capacity"> - Size of vertex array to store the vertices.</param>
		/// <returns>true if file has been opened successfully, otherwise returns false.</returns>
		bool8 LoadOBJ( const char* filePath, const uint32 capacity );

		bool8 LoadOBJ( const char* filePath );

	// Accessors:

		inline dx9::Vertex* GetVertices() { return m_Vertices; }

		inline uint32*      GetIndices()  { return m_Indices; };

		inline const uint32& GetVerticesAmount() const { return m_VerticesAmount; }

		inline const uint32& GetIndicesAmount()  const { return m_IndicesAmount; }

	private:

	// Private Functions:

		void ClearBuffers();

	// Buffers:

		dx9::Vertex* m_Vertices = nullptr;

		uint32*      m_Indices  = nullptr;

	// Vertices and Indices loaded amount:

		uint32 m_VerticesAmount = 0u;
		
		uint32 m_IndicesAmount  = 0u;
	};
}

#endif // OBJLOADER_H