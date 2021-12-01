#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "D3DUtility.h"
#include "Vertex.h"
#include "VertexMesh.h"

namespace dx9
{
	class RenderSystem
	{
	public:

	// Constructors and Destructor:

		RenderSystem( HWND hWnd, int32 width, int32 height );

		~RenderSystem();

	// Functions:

		// CREATE MESH BOX TEST
		ID3DXMesh* CreateMesh();
		ID3DXMesh* CreateMesh( std::vector<Vertex>& vertices, std::vector<DWORD>& indices );

		// TEST
		void CreateVertexBuffer();

		// TEST
		void CreateIndexBuffer();

		// TEST
		void CreateMaterial();

		// TEST
		void CreateLight( const D3DXVECTOR3& position, const D3DXCOLOR& color );

		// TEST
		void CreateTexture( const char* filePath );

		// TEST
		void SetView();

		// TEST DUMP
		void DumpVertices( std::ofstream& outFile, ID3DXMesh* mesh );
		void DumpIndices( std::ofstream& outFile, ID3DXMesh* mesh );
		void DumpAttributeBuffer( std::ofstream& outFile, ID3DXMesh* mesh );
		void DumpAdjacencyBuffer( std::ofstream& outFile, ID3DXMesh* mesh );
		void DumpAttributeTable( std::ofstream& outFile, ID3DXMesh* mesh );

		// TEST
		void Render( const float& dt );	

		void Render( ID3DXMesh* mesh, const float& dt );

	// Accessors:

		IDirect3DDevice9& GetDevice() const;

	private:

	// Variables:

		HWND m_phWnd = nullptr;


		int32 m_Width  = 0;

		int32 m_Height = 0;


		bool8 m_bWindowed = true;


		IDirect3DVertexBuffer9* m_pVertexBuffer = nullptr;

		IDirect3DIndexBuffer9* m_pIndexBuffer   = nullptr;

		D3DMATERIAL9 m_Material = {};

		D3DLIGHT9 m_Light = {};

		IDirect3DTexture9* m_pTexture;

	// Temporary Mesh:

		IDirect3DTexture9* m_pMeshTextures[3] = { nullptr, nullptr, nullptr };

		std::ofstream m_OutFile;


		IDirect3D9* m_pDirect3D  = nullptr;

		D3DCAPS9 m_DeviceCapabilities = {};

		int32 m_VertexProcessing = 0;

		D3DPRESENT_PARAMETERS m_PresentParameters = {};

		D3DDEVTYPE m_DeviceType = D3DDEVTYPE_HAL;

		D3DVIEWPORT9 m_Viewport = {};

		IDirect3DDevice9* m_pDevice = nullptr;
	};
}

#endif // RENDERSYSTEM_H