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
		//	m_VertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}
		else
		{
			MessageBoxA( nullptr, "ERROR::No hardware vertex processing available!", "RenderSystem", 0u );

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
		m_Viewport.MinZ   = 0.0f;
		m_Viewport.MaxZ   = 0.0f;
		
		m_pDevice->SetViewport(&m_Viewport);
	}

	RenderSystem::~RenderSystem()
	{
		m_phWnd = nullptr;

		dx9::Release( m_pDirect3D );

		dx9::Release( m_pDevice );
	}


// Functions:

	void RenderSystem::CreateMaterial()
	{
		m_Material.Ambient  = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		m_Material.Diffuse  = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		m_Material.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		m_Material.Emissive = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
		m_Material.Power    = 5.0f;

		m_pDevice->SetMaterial( &m_Material );
	}

	void RenderSystem::CreateLight( const D3DXVECTOR3& position,  const D3DXCOLOR& color )
	{
		::ZeroMemory( &m_Light, sizeof(m_Light) );

		m_Light.Type         = D3DLIGHT_SPOT;
		m_Light.Position     = position;
		m_Light.Direction    = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
		m_Light.Ambient      = color * 0.6f;
		m_Light.Diffuse      = color;
		m_Light.Specular     = color * 0.3f;		
		m_Light.Range        = 500.0f;
		m_Light.Falloff      = 1.0f;
		m_Light.Attenuation0 = 1.0f;
		m_Light.Attenuation1 = 0.0f;
		m_Light.Attenuation2 = 0.0f;
		m_Light.Theta        = 0.4f;
		m_Light.Phi          = 0.9f;

		m_pDevice->SetLight( 0u, &m_Light);
		m_pDevice->LightEnable( 0u, TRUE );
	}

	void RenderSystem::CreateTexture(const char* filePath)
	{
		D3DXCreateTextureFromFileA( m_pDevice, filePath, &m_pTexture );

		m_pDevice->SetTexture( 0, m_pTexture );

		m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT  );
	}

	void RenderSystem::SetView( const float& dt )
	{
	// Set render state:

		// Lights on.
		m_pDevice->SetRenderState( D3DRS_LIGHTING        , true );
		m_pDevice->SetRenderState( D3DRS_SPECULARENABLE  , true );
		m_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS, true );

	//	// Switch to wireframe mode.
	//	m_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	//
		// Turn on Gouraud interpolater pixel shading.
	//	m_pDevice->SetRenderState(D3DRS_LIGHTING , false);
	//	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// Position and aim the camera.

		static float32 distance_z = 0.0f;

		distance_z += dt;

		D3DXVECTOR3 position( 0.0f, 0.0f, distance_z );
		D3DXVECTOR3 target( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );
		D3DXMATRIX view = {};

		D3DXMatrixLookAtLH(&view, &position, &target, &up);

		m_pDevice->SetTransform( D3DTS_VIEW, &view);

	// Set the projection matrix.

		D3DXMATRIX proj = {};

		D3DXMatrixPerspectiveFovLH( &proj,
			                        D3DX_PI * 0.5f, // 90 - degree
			                        static_cast<float32>(m_Width) / static_cast<float32>(m_Height),
			                        1.0f,
			                        1000.0f);

		m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);		
	}

	void RenderSystem::SetWorldTransformFromInput( const float& dt )
	{
	// Spin the cube:

		D3DXMATRIX RotationX;
		D3DXMATRIX RotationY;
		D3DXMATRIX RotationZ;

		D3DXMATRIX Scaling;
		D3DXMATRIX Translation;

		static float32 scale = 1.0f;

		D3DXMatrixScaling( &Scaling, scale, scale, scale );

		static float32 tx = 0.0f;
		static float32 ty = 0.0f;
		static float32 tz = 0.0f;

		D3DXMatrixTranslation( &Translation, tx, ty, tz);

	// Rotate x-axis:

		static float32 x = 0.0f;
		D3DXMatrixRotationX( &RotationX, x );

	// Rotate y-axis:

		static float32 y = 0.0f;
		D3DXMatrixRotationY( &RotationY, y );

	// Rotate z-axis:

		static float32 z = 0.0f;
		D3DXMatrixRotationZ( &RotationZ, z );

	// TEST CONTROLS:

		if (::GetAsyncKeyState('I') & 0x8000f)
		{
			x -= dt;
		}
		else if (::GetAsyncKeyState('K') & 0x8000f)
		{
			x += dt;
		}
		
		if (::GetAsyncKeyState('L') & 0x8000f)
		{
			y += dt;
		}
		else if (::GetAsyncKeyState('J') & 0x8000f)
		{
			y -= dt;
		}

		if (::GetAsyncKeyState('Q') & 0x8000f)
		{
			this->SetView( dt * 20.0f );
		}
		else if (::GetAsyncKeyState('E') & 0x8000f)
		{
			this->SetView( -dt * 20.0f );
		}

		if (::GetAsyncKeyState('R') & 0x8000f)
		{
			scale -= dt;
		}
		else if (::GetAsyncKeyState('T') & 0x8000f)
		{
			scale += dt;
		}

		if (::GetAsyncKeyState('W') & 0x8000f)
		{
			ty += dt * 10.0f;
		}
		else if (::GetAsyncKeyState('S') & 0x8000f)
		{
			ty -= dt * 10.0f;
		}

		if (::GetAsyncKeyState('A') & 0x8000f)
		{
			tx -= dt * 10.0f;
		}
		else if (::GetAsyncKeyState('D') & 0x8000f)
		{
			tx += dt * 10.0f;
		}

	// Combine x-axis, y-axis and z-axis rotation transformations:

		D3DXMATRIX WorldMatrix = Translation * Scaling * RotationX * RotationY * RotationZ;

		m_pDevice->SetTransform( D3DTS_WORLD, &WorldMatrix);
	}

	void RenderSystem::Clear( D3DCOLOR color )
	{
		m_pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 );
		m_pDevice->BeginScene();
	}

	void RenderSystem::Render( Drawable& object )
	{
	// Draw object:

		object.Draw();
	}

	void RenderSystem::Display()
	{
		m_pDevice->EndScene();
		m_pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}


// Accessors:

	IDirect3DDevice9* RenderSystem::GetDevice() const
	{
		return m_pDevice;
	}

}