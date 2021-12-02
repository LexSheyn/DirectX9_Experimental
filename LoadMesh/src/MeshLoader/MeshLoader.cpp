#include "../PrecompiledHeaders/stdafx.h"
#include "MeshLoader.h"

namespace dx9
{
// Constructors and Destructor:

	MeshLoader::MeshLoader()
	{
	}

	MeshLoader::MeshLoader( HWND hWnd )
		: phWnd( hWnd )
	{
	}

	MeshLoader::~MeshLoader()
	{
		for ( auto& mesh : m_Meshes )
		{
			dx9::Release( mesh );
		}
	}


// Functions:

	bool8 MeshLoader::LoadMesh(const char* filePath)
	{
	// Start the import on the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll t
	// probably to request more postprocessing than we do in this example.

		const aiScene* scene = aiImportFile( filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices );

	// If the import failed, report it:

		if ( !scene )
		{
			MessageBoxA( phWnd, aiGetErrorString(), "Assimp Error", 0u );

			return false;
		}

	// Now we can access the file's contents:

		m_Meshes.resize( scene->mNumMeshes );

		for ( uint32 i = 0u; i < scene->mNumMeshes; i++ )
		{
			m_Meshes[i] = this->CopyMesh(scene->mMeshes[i]);
		}

	// We're done. Release all resources associated with this import:

		aiReleaseImport( scene );

		return true;
	}

	std::vector<ID3DXMesh*>& MeshLoader::GetMeshes()
	{
		return m_Meshes;
	}


// Modifiers:

	void MeshLoader::SetOutputWindow(HWND hWnd)
	{
		this->phWnd = hWnd;
	}

	void MeshLoader::SetD3DDevice(IDirect3DDevice9* pDevice)
	{
		this->pDevice = pDevice;
	}


// Private Functions:

	ID3DXMesh* MeshLoader::CopyMesh( aiMesh* iMesh )
	{
	// Create mesh:

		ID3DXMesh* mesh = nullptr;

		D3DXCreateMeshFVF( iMesh->mNumFaces, iMesh->mNumVertices, D3DXMESH_MANAGED | D3DXMESH_32BIT, Vertex::FVF, pDevice, &mesh );

	// Fill Vertices:
		
		std::vector<Vertex> tempVertices;

		tempVertices.resize( iMesh->mNumVertices );

		for ( size_t i = 0u; i < iMesh->mNumVertices; i++ )
		{
		// Position:

			if ( iMesh->HasPositions() )
			{
				tempVertices[i].position.x = iMesh->mVertices[i].x;
				tempVertices[i].position.y = iMesh->mVertices[i].y;
				tempVertices[i].position.z = iMesh->mVertices[i].z;
			}

		// Normal:

			if ( iMesh->HasNormals() )
			{
				tempVertices[i].normal.x = iMesh->mNormals[i].x;
				tempVertices[i].normal.y = iMesh->mNormals[i].y;
				tempVertices[i].normal.z = iMesh->mNormals[i].z;
			}			

		// Texture coordinate:

			if ( iMesh->HasTextureCoords( 0 ) && iMesh->HasTextureCoords( 1 ) )
			{
				tempVertices[i].textureCoord.x = iMesh->mTextureCoords[i]->x;
				tempVertices[i].textureCoord.y = iMesh->mTextureCoords[i]->y;
			}			
		}

		void* vertices = nullptr;

		mesh->LockVertexBuffer( 0u, (void**)&vertices );

		memcpy_s( vertices, iMesh->mNumVertices * sizeof(Vertex), tempVertices.data(), iMesh->mNumVertices * sizeof(Vertex) );

		mesh->UnlockVertexBuffer();

	// Fill Indices:

		void* indices = nullptr;

		mesh->LockIndexBuffer( 0, (void**)&indices );

		memcpy_s( indices, iMesh->mFaces->mNumIndices * sizeof(uint32), iMesh->mFaces->mIndices, iMesh->mFaces->mNumIndices * sizeof(uint32) );

		mesh->UnlockIndexBuffer();

	// FIll Attribute buffer:

		DWORD* attribute_buffer = nullptr;

		mesh->LockAttributeBuffer( 0, &attribute_buffer );

		// Group a:
		for ( uint32 a = 0u; a < iMesh->mNumFaces; a++ )
		{
			attribute_buffer[a] = 0u;
		}

		mesh->UnlockAttributeBuffer();

	// Optimize Mesh to generate an attrubute table:

		std::vector<DWORD> adjacency_buffer( mesh->GetNumFaces() * 3u );

		mesh->GenerateAdjacency( 0.0f, &adjacency_buffer[0] );

		mesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &adjacency_buffer[0], nullptr, nullptr, nullptr );

	// Load Materials:

		//

//	// Load Textures:
//
//		m_pMeshTextures[0] = iPtrTextures[0];

		return mesh;
	}

}