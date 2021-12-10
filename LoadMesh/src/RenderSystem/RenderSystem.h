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

		// TEST
		void CreateMaterial();

		// TEST
		void CreateLight( const D3DXVECTOR3& position, const D3DXCOLOR& color );

		// TEST
		void CreateTexture( const char* filePath );

		// TEST
		void SetView( const float& dt );

		/// <summary>
		/// Test function, handles all input fro setting scene transformation matrix.
		/// </summary>
		/// <param name="dt">
		/// - Delta time applied to all transformations as a coefficient.
		/// </param>
		void SetTransformationFromInput( const float& dt );

		void Clear( D3DCOLOR color = Color::DarkGray );

		void Render( Drawable& object );

		void Display();

	// Accessors:

		IDirect3DDevice9* GetDevice() const;

	private:

	// Variables:

		HWND m_phWnd = nullptr;

		int32 m_Width  = 0;

		int32 m_Height = 0;

		bool8 m_bWindowed = true;

	// Temporary mesh components:

		D3DMATERIAL9 m_Material = {};

		D3DLIGHT9 m_Light = {};

		IDirect3DTexture9* m_pTexture;

	// Components:

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