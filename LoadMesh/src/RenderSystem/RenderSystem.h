#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "D3DUtility.h"
#include "Vertex.h"

namespace dx9
{
	class RenderSystem
	{
	public:

	// Constructors and Destructor:

		RenderSystem( HWND hWnd, int32 width, int32 height );

		~RenderSystem();

	// Functions:

		// TEST
		void CreateVertexBuffer();

		// TEST
		void CreateIndexBuffer();

		// TEST
		void SetView();

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