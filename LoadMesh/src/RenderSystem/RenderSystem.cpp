#include "../PrecompiledHeaders/stdafx.h"
#include "RenderSystem.h"

namespace dx9
{
// Constructors and Destructor:

	RenderSystem::RenderSystem( HWND hWnd, int32 width, int32 height )
		: m_phWnd( hWnd ),
		  m_Width( width ),
		  m_Height( height )
	{
	// Step 1: Create the IDirect3D9 object:

		m_pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

	// Step 2: Check for hardware vertex processing:

		m_pDirect3D->GetDeviceCaps( D3DADAPTER_DEFAULT, m_DeviceType, &m_DeviceCapabilities );

		if ( m_DeviceCapabilities.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			m_VertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			MessageBoxA( nullptr, "No hardware vertex processing available!", "Error", 0u );

			return;
		}		

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure:

		m_PresentParameters.BackBufferWidth            = m_Width;
		m_PresentParameters.BackBufferHeight           = m_Height;
		m_PresentParameters.Windowed                   = m_bWindowed;
		m_PresentParameters.BackBufferCount            = 1u;
		m_PresentParameters.BackBufferFormat           = D3DFMT_A8R8G8B8;		
		m_PresentParameters.MultiSampleType            = D3DMULTISAMPLE_NONE;
		m_PresentParameters.MultiSampleQuality         = 0u;		
		m_PresentParameters.hDeviceWindow              = m_phWnd;		
		m_PresentParameters.Flags                      = 0u;
		m_PresentParameters.EnableAutoDepthStencil     = TRUE;
		m_PresentParameters.AutoDepthStencilFormat     = D3DFMT_D24S8;		
		m_PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_PresentParameters.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_PresentParameters.SwapEffect                 = D3DSWAPEFFECT_DISCARD;

	// Step 4: Create the device:

		m_pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
			                       m_DeviceType,
			                       m_phWnd,
			                       m_VertexProcessing,
			                       &m_PresentParameters,
			                       &m_pDevice);

	// Create Viewport:

		ZeroMemory(&m_Viewport, sizeof(D3DVIEWPORT9));
	
		m_Viewport.X      = 0;
		m_Viewport.Y      = 0;
		m_Viewport.Width  = m_Width;
		m_Viewport.Height = m_Height;
		m_Viewport.MinZ   = 0;
		m_Viewport.MaxZ   = 1;
		
		m_pDevice->SetViewport(&m_Viewport);
	}

	RenderSystem::~RenderSystem()
	{
		m_phWnd = nullptr;

		m_pDirect3D->Release();

		m_pDevice->Release();

		m_pVertexBuffer->Release();

		m_pIndexBuffer->Release();
	}


// Functions:

	void RenderSystem::CreateVertexBuffer()
	{
	//
	// Create vertex buffer:
	//

		m_pDevice->CreateVertexBuffer( 8u * sizeof(Vertex),
			                           D3DUSAGE_WRITEONLY,
			                           Vertex::FVF,
			                           D3DPOOL_MANAGED,
			                           &m_pVertexBuffer,
			                           nullptr);

		void* pVertices = nullptr;

		m_pVertexBuffer->Lock( 0u, 0u, (void**)&pVertices, 0 );

	// Vertices of a unit cube:

		Vertex vertices[8];

		vertices[0] = Vertex( -1.0f, -1.0f, -1.0f, Color::Red );
		vertices[1] = Vertex( -1.0f,  1.0f, -1.0f, Color::Red );
		vertices[2] = Vertex(  1.0f,  1.0f, -1.0f, Color::Green );
		vertices[3] = Vertex(  1.0f, -1.0f, -1.0f, Color::Green );
		vertices[4] = Vertex( -1.0f, -1.0f,  1.0f, Color::Blue );
		vertices[5] = Vertex( -1.0f,  1.0f,  1.0f, Color::Blue );
		vertices[6] = Vertex(  1.0f,  1.0f,  1.0f, Color::White );
		vertices[7] = Vertex(  1.0f, -1.0f,  1.0f, Color::White );

		memcpy_s( pVertices, sizeof(vertices), vertices, sizeof(vertices) );

		m_pVertexBuffer->Unlock();
	}

	void RenderSystem::CreateIndexBuffer()
	{
	// Create index buffers.

		m_pDevice->CreateIndexBuffer( 36u * sizeof(WORD),
			                          D3DUSAGE_WRITEONLY,
			                          D3DFMT_INDEX16,
			                          D3DPOOL_MANAGED,
			                          &m_pIndexBuffer,
			                          nullptr);

		void* pIndices = nullptr;

		m_pIndexBuffer->Lock( 0, 0, (void**)&pIndices, 0 );

		WORD indices[36] = {};

		// front side
		indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
		indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

		// back side
		indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
		indices[9]  = 4; indices[10] = 7; indices[11] = 6;

		// left side
		indices[12] = 4; indices[13] = 5; indices[14] = 1;
		indices[15] = 4; indices[16] = 1; indices[17] = 0;

		// right side
		indices[18] = 3; indices[19] = 2; indices[20] = 6;
		indices[21] = 3; indices[22] = 6; indices[23] = 7;

		// top
		indices[24] = 1; indices[25] = 5; indices[26] = 6;
		indices[27] = 1; indices[28] = 6; indices[29] = 2;

		// bottom
		indices[30] = 4; indices[31] = 0; indices[32] = 3;
		indices[33] = 4; indices[34] = 3; indices[35] = 7;

		memcpy_s( pIndices, sizeof(indices), indices, sizeof(indices) );

		m_pIndexBuffer->Unlock();
	}

	void RenderSystem::SetView()
	{
	// Position and aim the camera.

		D3DXVECTOR3 position( 0.0f, 0.0f, -5.0f );
		D3DXVECTOR3 target( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );
		D3DXMATRIX view;

		D3DXMatrixLookAtLH(&view, &position, &target, &up);

		m_pDevice->SetTransform( D3DTS_VIEW, &view);

	// Set the projection matrix.

		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH( &proj,
			                        D3DX_PI * 0.5f, // 90 - degree
			                        21.0f / 9.0f,
			                        1.0f,
			                        1000.0f);

		m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);

	// Switch to wireframe mode.

	//	m_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	// Turn on Gouraud interpolater pixel shading:

		m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	}

	void RenderSystem::Render( const float& dt )
	{
	// Spin the cube:

		D3DXMATRIX Rx, Ry;

	// rotate 45 degrees on x-axis:

		D3DXMatrixRotationX( &Rx, 3.14f / 4.0f);

	// incremement y-rotation angle each frame:

		static float32 y = 0.0f;

		D3DXMatrixRotationY( &Ry, y );

		y += dt;

	// reset angle to zero when angle reaches 2*PI:

		if (y >= 6.28f)
		{
			y = 0.0f;
		}

	// Combine x-axis and y-axis rotation transformations:

		D3DXMATRIX p = Rx * Ry;

		m_pDevice->SetTransform( D3DTS_WORLD, &p );

	// Draw the scene:

		m_pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x66666666, 1.0f, 0 );
		m_pDevice->BeginScene();

		m_pDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(Vertex) );
		m_pDevice->SetFVF(Vertex::FVF);
		m_pDevice->SetIndices( m_pIndexBuffer );		

	// Draw cube:

		m_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0u, 8u, 0u, 12u );

		// TEST
	//	ID3DXMesh* mesh = nullptr;
	//	D3DXCreateTorus( m_pDevice, 1.0f, 2.0f, 30u, 30u, &mesh, nullptr );
	//	mesh->DrawSubset(0);
		
		m_pDevice->EndScene();
		m_pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}
	
	void RenderSystem::Render(ID3DXMesh* mesh, const float& dt)
	{
	// Spin the cube:

		D3DXMATRIX Rx, Ry;

	// rotate 45 degrees on x-axis:

		D3DXMatrixRotationX( &Rx, 3.14f / 4.0f);

	// incremement y-rotation angle each frame:

		static float32 y = 0.0f;

		D3DXMatrixRotationY( &Ry, y );

		y += dt;

	// reset angle to zero when angle reaches 2*PI:

		if (y >= 6.28f)
		{
			y = 0.0f;
		}

	// Combine x-axis and y-axis rotation transformations:

		D3DXMATRIX p = Rx * Ry;

		m_pDevice->SetTransform( D3DTS_WORLD, &p );

	// Draw the scene:

		m_pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x66666666, 1.0f, 0 );
		m_pDevice->BeginScene();

	//	D3DXCreateTorus( m_pDevice, 1.0f, 2.0f, 30u, 30u, &mesh, nullptr );
		mesh->DrawSubset(0);
		
		m_pDevice->EndScene();
		m_pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}


// Accessors:

	IDirect3DDevice9& RenderSystem::GetDevice() const
	{
		return *m_pDevice;
	}
}