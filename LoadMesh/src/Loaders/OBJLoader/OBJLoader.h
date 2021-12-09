#ifndef OBJLOADER_H
#define OBJLOADER_H

// Components:
#include "Position.h"
#include "TextureCoord.h"
#include "Normal.h"

// External dependancies:
#include "../../RenderSystem/D3DUtility.h"
#include "../../RenderSystem/Vertex.h"

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
		/// Load Vertex positions, texture coordinates, normals and faces amount from .obj file to the buffer.
		/// </summary>
		/// <param name="filePath">
		/// - Full path to the .obj file.
		/// </param>
		/// <param name="findMaterials">
		/// - Look for all materials in the same directory and load all materials found.
		/// </param>
		/// <returns>
		/// TRUE if file has been opened successfully, otherwise returns FALSE.
		/// </returns>
		bool8 LoadOBJ( const char* pathToOBJ, const bool findMaterials = false );

		/// <summary>
		/// Load Material from .mtl file to the buffer.
		/// </summary>
		/// <param name="filePath">
		/// - Full path to the .mtl file.
		/// </param>
		/// <returns>
		/// TRUE if file has been opened successfully, otherwise returns FALSE.
		/// </returns>
		bool8 LoadMaterial( const char* pathToMTL );

		void ClearGeometryBuffer();

		void ClearMaterialsBuffer();

	// Accessors:

		inline const uint32&              GetVerticesAmount() const { return m_VerticesAmount; }

		inline const uint32&              GetFacesAmount()    const { return m_FacesAmount; }

		inline std::vector<dx9::Vertex>&  GetVertices()             { return m_Vertices; }

		inline std::vector<D3DMATERIAL9>& GetMaterials()            { return m_Materials; }

	private:

	// Vertices and Faces loaded amount:

		uint32 m_VerticesAmount  = 0u;

		uint32 m_FacesAmount     = 0u;

		uint32 m_MaterialsAmount = 0u;

	// Buffers:

		std::vector<dx9::Vertex>  m_Vertices;

		std::vector<D3DMATERIAL9> m_Materials;
	};
}

#endif // OBJLOADER_H