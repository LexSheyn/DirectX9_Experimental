#include "../PrecompiledHeaders/stdafx.h"
#include "RenderSystem.h"

namespace dx9
{
	D3DVERTEXELEMENT9 VertElement[] =
	{
		{0, 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL  , 0},
		{0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	};

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

		dx9::Release( m_pDirect3D );

		dx9::Release( m_pDevice );

		dx9::Release( m_pVertexBuffer );

		dx9::Release( m_pIndexBuffer );

		dx9::Release( m_pMesh );

		for ( auto* texture : m_pMeshTextures )
		{
			dx9::Release( texture );
		}
	}


// Functions:

	ID3DXMesh* RenderSystem::CreateMesh()
	{
		m_pMesh = nullptr;
		
		HRESULT result = D3DXCreateMeshFVF( 12, 24, D3DXMESH_MANAGED, VertexMesh::FVF, m_pDevice, &m_pMesh );

		if ( FAILED(result) )
		{
			MessageBoxA( m_phWnd, "Failed to create mesh with D3DXCreateMeshFVF(...)", "ERROR:RendeSystem::CreateMesh", 0u );
		
			return nullptr;
		}

	// Fill Vertices:

		VertexMesh* vertices = nullptr;

		m_pMesh->LockVertexBuffer( 0u, (void**)&vertices );

		// fill in the front face vertex data
		vertices[0]  = VertexMesh( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f );
		vertices[1]  = VertexMesh( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f );
		vertices[2]  = VertexMesh(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f );
		vertices[3]  = VertexMesh(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f );
					    
		// fill in the  back face vertex data
		vertices[4]  = VertexMesh( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f );
		vertices[5]  = VertexMesh(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f );
		vertices[6]  = VertexMesh(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f );
		vertices[7]  = VertexMesh( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f );
					    					 
		// fill in the  top face vertex data 
		vertices[8]  = VertexMesh( -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f );
		vertices[9]  = VertexMesh( -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f );
		vertices[10] = VertexMesh(  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f );
		vertices[11] = VertexMesh(  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  bottom face vertex data
		vertices[12] = VertexMesh( -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f );
		vertices[13] = VertexMesh(  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f );
		vertices[14] = VertexMesh(  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f );
		vertices[15] = VertexMesh( -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  left face vertex data
		vertices[16] = VertexMesh( -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
		vertices[17] = VertexMesh( -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
		vertices[18] = VertexMesh( -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
		vertices[19] = VertexMesh( -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  right face vertex data
		vertices[20] = VertexMesh(  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
		vertices[21] = VertexMesh(  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
		vertices[22] = VertexMesh(  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
		vertices[23] = VertexMesh(  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f );

		m_pMesh->UnlockVertexBuffer();

	// Fill Indices:

		WORD* indices = nullptr;

		m_pMesh->LockIndexBuffer( 0, (void**)&indices );

		// front side
		indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
		indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

		// back side
		indices[6]  = 4; indices[7]  = 5; indices[8]  = 6;
		indices[9]  = 4; indices[10] = 6; indices[11] = 7;

		// left side
		indices[12] = 8; indices[13] = 9; indices[14] = 10;
		indices[15] = 8; indices[16] = 10; indices[17] = 11;

		// right side
		indices[18] = 12; indices[19] = 13; indices[20] = 14;
		indices[21] = 12; indices[22] = 14; indices[23] = 15;

		// top
		indices[24] = 16; indices[25] = 17; indices[26] = 18;
		indices[27] = 16; indices[28] = 18; indices[29] = 19;

		// bottom
		indices[30] = 20; indices[31] = 21; indices[32] = 22;
		indices[33] = 20; indices[34] = 22; indices[35] = 23;

		m_pMesh->UnlockIndexBuffer();

	// FIll Attribute buffer:

		DWORD* attribute_buffer = nullptr;

		m_pMesh->LockAttributeBuffer( 0, &attribute_buffer );

		// Group a:
		for ( uint32 a = 0u; a < 4u; a++)
		{
			attribute_buffer[a] = 0u;
		}

		// Group b:
		for ( uint32 b = 4u; b < 8u; b++ )
		{
			attribute_buffer[b] = 1u;
		}

		// Group c:
		for ( uint32 c = 8u; c < 12u; c++ )
		{
			attribute_buffer[c] = 2u;
		}

		m_pMesh->UnlockAttributeBuffer();

	// Optimize Mesh to generate an attrubute table:

		std::vector<DWORD> adjacency_buffer( m_pMesh->GetNumFaces() * 3u );

		m_pMesh->GenerateAdjacency( 0.0f, &adjacency_buffer[0] );

		result = m_pMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &adjacency_buffer[0], nullptr, nullptr, nullptr );

		if (FAILED(result))
		{
			MessageBoxA( m_phWnd, "Failed to optimize mesh with OptimizeInplace(...)", "ERROR:RendeSystem::CreateMesh", 0u );
	
			return nullptr;
		}

	// Dump the Mesh data to file:

		m_OutFile.open( "C:/TemporaryStorage/MeshDump.txt" );

	//	this->DumpVertices( m_OutFile, m_pMesh );
	//	this->DumpIndices( m_OutFile, m_pMesh );
	//	this->DumpAttributeBuffer( m_OutFile, m_pMesh );
	//	this->DumpAdjacencyBuffer( m_OutFile, m_pMesh );
	//	this->DumpAttributeTable( m_OutFile, m_pMesh );

		m_OutFile.close();

	// Load Textures and set filters:

		D3DXCreateTextureFromFileA( m_pDevice, "C:/TemporaryStorage/Geass_256x256.png", &m_pMeshTextures[0] );
		D3DXCreateTextureFromFileA( m_pDevice, "C:/TemporaryStorage/Geass_256x256.png", &m_pMeshTextures[1] );
		D3DXCreateTextureFromFileA( m_pDevice, "C:/TemporaryStorage/Geass_256x256.png", &m_pMeshTextures[2] );

		m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT  );

		return m_pMesh;
	}

	void RenderSystem::CreateVertexBuffer()
	{
	// Create Vertices:

		Vertex vertices[24];

	// Create vertex buffer:

		m_pDevice->CreateVertexBuffer( std::size(vertices) * sizeof(Vertex),
			                           D3DUSAGE_WRITEONLY,
			                           Vertex::FVF,
			                           D3DPOOL_MANAGED,
			                           &m_pVertexBuffer,
			                           nullptr);

		void* pVertices = nullptr;

		m_pVertexBuffer->Lock( 0u, 0u, (void**)&pVertices, 0 );

	// Vertices of a unit cube:
				
		// fill in the front face vertex data
		vertices[0]  = Vertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, Color::White );
		vertices[1]  = Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, Color::White );
		vertices[2]  = Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, Color::White );
		vertices[3]  = Vertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, Color::White );
					    
		// fill in the  back face vertex data
		vertices[4]  = Vertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, Color::White );
		vertices[5]  = Vertex(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, Color::White );
		vertices[6]  = Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, Color::White );
		vertices[7]  = Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, Color::White );
					    					 
		// fill in the  top face vertex data 
		vertices[8]  = Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, Color::White );
		vertices[9]  = Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, Color::White );
		vertices[10] = Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, Color::White );
		vertices[11] = Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, Color::White );
					    
		// fill in the  bottom face vertex data
		vertices[12] = Vertex( -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, Color::White );
		vertices[13] = Vertex(  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, Color::White );
		vertices[14] = Vertex(  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, Color::White );
		vertices[15] = Vertex( -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, Color::White );
					    
		// fill in the  left face vertex data
		vertices[16] = Vertex( -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, Color::White );
		vertices[17] = Vertex( -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, Color::White );
		vertices[18] = Vertex( -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, Color::White );
		vertices[19] = Vertex( -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, Color::White );
					    
		// fill in the  right face vertex data
		vertices[20] = Vertex(  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, Color::White );
		vertices[21] = Vertex(  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, Color::White );
		vertices[22] = Vertex(  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, Color::White );
		vertices[23] = Vertex(  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, Color::White );

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
		indices[6]  = 4; indices[7]  = 5; indices[8]  = 6;
		indices[9]  = 4; indices[10] = 6; indices[11] = 7;

		// left side
		indices[12] = 8; indices[13] = 9; indices[14] = 10;
		indices[15] = 8; indices[16] = 10; indices[17] = 11;

		// right side
		indices[18] = 12; indices[19] = 13; indices[20] = 14;
		indices[21] = 12; indices[22] = 14; indices[23] = 15;

		// top
		indices[24] = 16; indices[25] = 17; indices[26] = 18;
		indices[27] = 16; indices[28] = 18; indices[29] = 19;

		// bottom
		indices[30] = 20; indices[31] = 21; indices[32] = 22;
		indices[33] = 20; indices[34] = 22; indices[35] = 23;

		memcpy_s( pIndices, sizeof(indices), indices, sizeof(indices) );

		m_pIndexBuffer->Unlock();
	}

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

		m_Light.Type         = D3DLIGHT_POINT;
		m_Light.Ambient      = color * 0.6f;
		m_Light.Diffuse      = color;
		m_Light.Specular     = color * 0.6f;
		m_Light.Position     = position;
		m_Light.Range        = 2.f;
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

	void RenderSystem::SetView()
	{
	// Set render state:

		// Lights on.
		m_pDevice->SetRenderState( D3DRS_LIGHTING        , false );
	//	m_pDevice->SetRenderState( D3DRS_SPECULARENABLE  , true );
	//	m_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS, true );

	//	// Switch to wireframe mode.
	//	m_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	//
	//	// Turn on Gouraud interpolater pixel shading.
	//	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// Position and aim the camera.

		D3DXVECTOR3 position( 0.0f, 0.0f, -5.0f );
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

	void RenderSystem::DumpVertices(std::ofstream& outFile, ID3DXMesh* mesh)
	{
		outFile << "Vertices:" << "\n";
		outFile << "---------" << "\n\n";

		Vertex* vertex = nullptr;

		mesh->LockVertexBuffer( 0, (void**)&vertex );

		for ( DWORD i = 0u; i < mesh->GetNumVertices(); i++ )
		{
			outFile << "Vertex " << i << ": (";

			outFile << vertex[i].position.x     << ", " << vertex[i].position.y     << ", " << vertex[i].position.z << ", ";
			outFile << vertex[i].normal.x       << ", " << vertex[i].normal.y       << ", " << vertex[i].normal.z << ", ";
			outFile << vertex[i].textureCoord.x << ", " << vertex[i].textureCoord.y << ")" << "\n";
		}

		mesh->UnlockVertexBuffer();

		outFile << "\n\n";
	}

	void RenderSystem::DumpIndices(std::ofstream& outFile, ID3DXMesh* mesh)
	{
		outFile << "Indices:" << "\n";
		outFile << "--------" << "\n\n";

		WORD* indices = nullptr;

		mesh->LockIndexBuffer(0, (void**)&indices);

		for ( DWORD i = 0u; i < mesh->GetNumFaces(); i++ )
		{
			outFile << "Triangle " << i << ": ";

			outFile << indices[i * 3]     << " ";
			outFile << indices[i * 3 + 1] << " ";
			outFile << indices[i * 3 + 2] << "\n";
		}

		mesh->UnlockIndexBuffer();

		outFile << "\n\n";
	}

	void RenderSystem::DumpAttributeBuffer(std::ofstream& outFile, ID3DXMesh* mesh)
	{
		outFile << "Attribute Buffer:" << "\n";
		outFile << "-----------------" << "\n\n";

		DWORD* attributeBuffer = nullptr;

		mesh->LockAttributeBuffer(0, &attributeBuffer);

	// An attribute for each face:

		for ( DWORD i = 0; i < mesh->GetNumFaces(); i++ )
		{
			outFile << "Triangle lives in subset " << i << ": ";
			outFile << attributeBuffer[i] << "\n";
		}
		
		mesh->UnlockAttributeBuffer();

		outFile << "\n\n";
	}

	void RenderSystem::DumpAdjacencyBuffer(std::ofstream& outFile, ID3DXMesh* mesh)
	{
		outFile << "Adjacency Buffer:" << std::endl;
		outFile << "-----------------" << std::endl << std::endl;

		// three enttries per face
		std::vector<DWORD> adjacencyBuffer(mesh->GetNumFaces() * 3);

		mesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

		for ( DWORD i = 0; i < mesh->GetNumFaces(); i++ )
		{
			outFile << "Triangle's adjacent to triangle " << i << ": ";
			outFile << adjacencyBuffer[i * 3] << " ";
			outFile << adjacencyBuffer[i * 3 + 1] << " ";
			outFile << adjacencyBuffer[i * 3 + 2] << std::endl;
		}

		outFile << std::endl << std::endl;
	}

	void RenderSystem::DumpAttributeTable(std::ofstream& outFile, ID3DXMesh* mesh)
	{
		outFile << "Attribute Table:" << std::endl;
		outFile << "----------------" << std::endl << std::endl;

		// number of entries in the attribute table
		DWORD numEntries = 0;

		mesh->GetAttributeTable(0, &numEntries);

		std::vector<D3DXATTRIBUTERANGE> table(numEntries);

		mesh->GetAttributeTable(&table[0], &numEntries);

		for ( DWORD i = 0; i < numEntries; i++ )
		{
			outFile << "Entry " << i << std::endl;
			outFile << "-----------" << std::endl;

			outFile << "Subset ID:    " << table[i].AttribId    << std::endl;
			outFile << "Face Start:   " << table[i].FaceStart   << std::endl;
			outFile << "Face Count:   " << table[i].FaceCount   << std::endl;
			outFile << "Vertex Start: " << table[i].VertexStart << std::endl;
			outFile << "Vertex Count: " << table[i].VertexCount << std::endl;
			outFile << std::endl;
		}

		outFile << std::endl << std::endl;
	}

	void RenderSystem::Render( const float& dt )
	{
	// Spin the cube:

		D3DXMATRIX Rx;
		D3DXMATRIX Ry;
		D3DXMATRIX Rz;

	// Rotate x-axis:

		static float32 x = 0.0f;

		D3DXMatrixRotationX( &Rx, x );

		x += dt;

	// Rotate y-axis:

		static float32 y = 0.0f;

		D3DXMatrixRotationY( &Ry, y );

		y += dt;

	// Rotate z-axis:

		static float32 z = 0.0f;

		D3DXMatrixRotationZ( &Rz, z );

		z += dt;

	// Combine x-axis, y-axis and z-axis rotation transformations:

		D3DXMATRIX p = Rx * Ry * Rz;

		m_pDevice->SetTransform( D3DTS_WORLD, &p );

	// Draw the scene:

		m_pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color::DarkGrey, 1.0f, 0 );
		m_pDevice->BeginScene();

		m_pDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(Vertex) );
		m_pDevice->SetFVF(Vertex::FVF);
		m_pDevice->SetIndices( m_pIndexBuffer );

	// Draw cube:

		m_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0u, 24u, 0u, 12u );
	//	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 4u );
		
		m_pDevice->EndScene();
		m_pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}
	
	void RenderSystem::Render(ID3DXMesh* mesh, const float& dt)
	{
	// Spin the cube:

		D3DXMATRIX Rx;
		D3DXMATRIX Ry;
		D3DXMATRIX Rz;

	// Rotate x-axis:

		static float32 x = 0.0f;

		D3DXMatrixRotationX( &Rx, x );

		x += dt;

	// Rotate y-axis:

		static float32 y = 0.0f;

		D3DXMatrixRotationY( &Ry, y );

		y += dt;

	// Rotate z-axis:

		static float32 z = 0.0f;

		D3DXMatrixRotationZ( &Rz, z );

		z += dt;

	// Combine x-axis, y-axis and z-axis rotation transformations:

		D3DXMATRIX p = Rx * Ry * Rz;

		m_pDevice->SetTransform( D3DTS_WORLD, &p );

	// Draw the scene:

		m_pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color::Pink, 1.0f, 0 );
		m_pDevice->BeginScene();

		for ( size_t i = 0u; i < std::size( m_pMeshTextures ); i++ )
		{
			m_pDevice->SetTexture( 0, m_pMeshTextures[i] );
			
			mesh->DrawSubset( i );
		}
		
		m_pDevice->EndScene();
		m_pDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}


// Accessors:

	IDirect3DDevice9& RenderSystem::GetDevice() const
	{
		return *m_pDevice;
	}
}