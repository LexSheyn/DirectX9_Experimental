#ifndef STLLOADER_H
#define STLLOADER_H

#include "Vector3F64.h"

#include "../../RenderSystem/Vertex.h"

namespace stl
{
	class STLLoader
	{
	public:

	// Constructors and Destructor:

		STLLoader();

		~STLLoader();

	// Functions:

		/// <summary>
		/// Load vertex positions and normals from .stl file.
		/// Textures, colours, materials... are not supported.
		/// </summary>
		/// <param name="pathToSTL">
		/// - Full path to the .stl file.
		/// </param>
		/// <returns>
		/// STL_SUCCESS if file was successfully opened and vertex data has loaded in, otherwise STLErrorCode.
		/// </returns>
		uint32 LoadSTL( const char* pathToSTL );

		void ClearBuffer();

	// Accessors:

		inline std::vector<dx9::Vertex>& GetVertices()          { return m_Vertices; }

		inline const uint32&             GetFacesAmount() const { return m_FacesAmount; }

	private:

	// Buffers:

		std::vector<dx9::Vertex> m_Vertices;

		uint32 m_VerticesAmount;

		uint32 m_FacesAmount;
	};
}

#endif // STLLOADER_H