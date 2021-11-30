#include "../PrecompiledHeaders/stdafx.h"
#include "MeshLoader.h"

namespace dx9
{
// Constructors and Destructor:

	MeshLoader::MeshLoader()
	{
	}

	MeshLoader::MeshLoader( HWND hWnd )
		: m_hWnd( hWnd )
	{
	}

	MeshLoader::~MeshLoader()
	{
	}


// Functions:

	bool8 MeshLoader::Load(const char* filePath)
	{
	// Start the import on the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll t
	// probably to request more postprocessing than we do in this example.

		const aiScene* scene = aiImportFile( filePath, 
		                                     aiProcess_CalcTangentSpace
		                                   | aiProcess_Triangulate
		                                   | aiProcess_JoinIdenticalVertices
		                                   | aiProcess_SortByPType);

	// If the import failed, report it:

		if ( !scene )
		{
			MessageBoxA( m_hWnd, aiGetErrorString(), "Assimg Error", 0u );

			return false;
		}

	// Now we can access the file's contents:

		// Get vertices, indices, materials... put them into the buffers...

	// We're done. Release all resources associated with this import:

		aiReleaseImport( scene );

		return true;
	}

}