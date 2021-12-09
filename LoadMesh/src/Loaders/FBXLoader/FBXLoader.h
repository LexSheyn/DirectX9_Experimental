#ifndef FBXLOADER_H
#define FBXLOADER_H

#include "FBXVertex.h"

// Autodesk FBX SDK:
//#include <fbxsdk.h>

namespace fbx
{
	class FBXLoader
	{
	public:

	// Constructors and Destructor:

		FBXLoader();
		FBXLoader( HWND phWnd );

		~FBXLoader();

	// Functions:

		/// <summary>
		/// Load Vertices and Indices from .fbx file into buffers.
		/// Materials would be added later...
		/// </summary>
		/// <param name="filePath"> - Full path to the .fbx file.</param>
		/// <returns>Error code, would be inplemented later...</returns>
		const uint32& LoadFBX( const char* filePath ) const;

	// Accessors:

		/// <summary>
		/// Get address of Vertex vector.
		/// </summary>
		/// <returns>m_Vertices</returns>
		inline std::vector<FBXVertex>& GetVertices() { return m_Vertices; }

		/// <summary>
		/// Get address of Index vector.
		/// </summary>
		/// <returns>m_Indices</returns>
		inline std::vector<uint32>&    GetIndices()	 { return m_Indices;  }

	// Modifiers:

		void SetWindowHandle( HWND phWnd );

	private:

	// Private Functions:

		/// <summary>
		/// Clears Vertices and Indices vectors.
		/// </summary>
		void ClearBuffers();

	// Window handle pointer:

		HWND m_phWnd;

	// Buffers:

		std::vector<FBXVertex> m_Vertices;

		std::vector<uint32>    m_Indices;

		// Materials would be here.

	// Errors (Should be moved into the separate class by the way):

		uint32 m_ErrorCode;
	};
}

#endif // FBXLOADER_H