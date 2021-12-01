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
			MessageBoxA( m_hWnd, aiGetErrorString(), "Assimp Error", 0u );

			return false;
		}

	// Now we can access the file's contents:

		if ( scene->HasMeshes() )
		{
			MessageBoxA( m_hWnd, "Meshes loaded!", "INFO::MeshLoader::Load", 0u );
			
			for ( uint32 i = 0u; i < scene->mNumMeshes; i++ )
			{
				MessageBoxA( m_hWnd, "Mesh detected!", "INFO::MeshLoader::Load", 0u );
			}
		}

		m_Meshes.resize( scene->mNumMeshes );

		for ( uint32 i = 0; i < scene->mNumMeshes; i++ )
		{
			m_Meshes[i] = *scene->mMeshes[i];
		}

	// We're done. Release all resources associated with this import:

		aiReleaseImport( scene );

		return true;
	}

	void MeshLoader::GetMeshes(std::vector<ID3DXMesh*>& meshes)
	{
	}

}