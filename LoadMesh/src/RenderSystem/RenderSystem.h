#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Color.h"
#include "Mesh.h"

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
		ID3DXMesh* CreateMesh( const std::vector<Vertex>& iVertices, 
			                   const std::vector<uint32>& iIndices,
			                         std::vector<D3DMATERIAL9>& iMaterials, 
			                         std::vector<IDirect3DTexture9*>& iPtrTextures );

		// TEST
		void CreateMaterial();

		// TEST
		void CreateLight( const D3DXVECTOR3& position, const D3DXCOLOR& color );

		// TEST
		void CreateTexture( const char* filePath );

		// TEST
		void SetView( const float& dt );

		void RenderIndexed( ID3DXMesh* mesh, const float& dt );

		void Render( Mesh& mesh, const float& dt );

	// Accessors:

		IDirect3DDevice9* GetDevice() const;

	private:

	// Private Functions:
		/*
		void LogVertices( std::ofstream& outFile, ID3DXMesh* mesh );
		void LogIndices( std::ofstream& outFile, ID3DXMesh* mesh );
		void LogAttributeBuffer( std::ofstream& outFile, ID3DXMesh* mesh );
		void LogAdjacencyBuffer( std::ofstream& outFile, ID3DXMesh* mesh );
		void LogAttributeTable( std::ofstream& outFile, ID3DXMesh* mesh );
		*/
	// Variables:

		HWND m_phWnd = nullptr;

		int32 m_Width  = 0;

		int32 m_Height = 0;

		bool8 m_bWindowed = true;

	// Temporary mesh components:

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

	// Disable unscoped enum warning:
	#pragma warning( push ) // C26812
	#pragma warning( disable : 26812)

		D3DDEVTYPE m_DeviceType = D3DDEVTYPE_HAL;

	#pragma warning( pop ) // C26812

		D3DVIEWPORT9 m_Viewport = {};

		IDirect3DDevice9* m_pDevice = nullptr;
	};
}

#endif // RENDERSYSTEM_H