#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1600, 900, "DirectX9_Test_Window" )
	{
	// Loading Mesh:

	//	m_MeshLoader.SetOutputWindow( m_Window.GetHandle() );
	//	m_MeshLoader.SetD3DDevice( m_Window.GetRenderSystem().GetDevice() );
	//
	//	m_MeshLoader.LoadMesh( "D:/Models/robo-obj-pose4/source/robot.obj" );
	//
	//	ID3DXMesh* test_mesh = m_MeshLoader.GetMeshes().at( 0 );
	//
	//	mesh = test_mesh;

		dx9::OBJLoader loader;

		bool8 result = false;

		result = loader.LoadOBJ( "D:/Models/ganesha-obj/source/ganesha.obj" );

		if ( result )
		{
			MessageBoxA( m_Window.GetHandle(), "Success!", "LoadOBJ", 0u );
		}
		else
		{
			MessageBoxA( m_Window.GetHandle(), "Failed!", "LoadOBJ", 0u );
		}

	// CREATE TEST MESH:

		std::vector<dx9::Vertex> vertices;

		vertices.resize( 24u );

		// fill in the front face vertex data
		vertices[0]  = dx9::Vertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f );
		vertices[1]  = dx9::Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f );
		vertices[2]  = dx9::Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f );
		vertices[3]  = dx9::Vertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f );
					    
		// fill in the  back face vertex data
		vertices[4]  = dx9::Vertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f );
		vertices[5]  = dx9::Vertex(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f );
		vertices[6]  = dx9::Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f );
		vertices[7]  = dx9::Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f );
					    					 
		// fill in the  top face vertex data 
		vertices[8]  = dx9::Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f );
		vertices[9]  = dx9::Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f );
		vertices[10] = dx9::Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f );
		vertices[11] = dx9::Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  bottom face vertex data
		vertices[12] = dx9::Vertex( -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f );
		vertices[13] = dx9::Vertex(  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f );
		vertices[14] = dx9::Vertex(  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f );
		vertices[15] = dx9::Vertex( -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  left face vertex data
		vertices[16] = dx9::Vertex( -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
		vertices[17] = dx9::Vertex( -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
		vertices[18] = dx9::Vertex( -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
		vertices[19] = dx9::Vertex( -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f );
					    
		// fill in the  right face vertex data
		vertices[20] = dx9::Vertex(  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
		vertices[21] = dx9::Vertex(  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
		vertices[22] = dx9::Vertex(  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
		vertices[23] = dx9::Vertex(  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f );

		std::vector<uint32> indices;

		indices.resize( 36u );

		// front side
		indices[0]   = 0; indices[1]  = 1;  indices[2]  = 2;
		indices[3]   = 0; indices[4]  = 2;  indices[5]  = 3;

		// back side
		indices[6]   = 4; indices[7]  = 5;  indices[8]  = 6;
		indices[9]   = 4; indices[10] = 6;  indices[11] = 7;

		// left side
		indices[12]  = 8; indices[13] = 9;  indices[14] = 10;
		indices[15]  = 8; indices[16] = 10; indices[17] = 11;

		// right side
		indices[18] = 12; indices[19] = 13; indices[20] = 14;
		indices[21] = 12; indices[22] = 14; indices[23] = 15;

		// top
		indices[24] = 16; indices[25] = 17; indices[26] = 18;
		indices[27] = 16; indices[28] = 18; indices[29] = 19;

		// bottom
		indices[30] = 20; indices[31] = 21; indices[32] = 22;
		indices[33] = 20; indices[34] = 22; indices[35] = 23;

		std::vector<D3DMATERIAL9> materials;

		std::vector<IDirect3DTexture9*> pTextures;

		pTextures.resize( 1u );

		D3DXCreateTextureFromFileA( m_Window.GetRenderSystem().GetDevice(), "D:/Documents and files/Downloads/ART/psycho-pass-we-heart-it.jpg", &pTextures[0] );
	
		mesh = m_Window.GetRenderSystem().CreateMesh( vertices, indices, materials, pTextures );

	//	m_Window.GetRenderSystem().CreateVertexBuffer();
	//	m_Window.GetRenderSystem().CreateIndexBuffer();
	//	m_Window.GetRenderSystem().CreateMaterial();
	//	m_Window.GetRenderSystem().CreateLight( D3DXVECTOR3( 0.0f, 0.3f, 0.25f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//	m_Window.GetRenderSystem().CreateTexture( "C:/TemporaryStorage/Geass_256x256.png" );
		m_Window.GetRenderSystem().SetView( 0.0f );

	//	D3DXCreateTorus( &m_Window.GetRenderSystem().GetDevice(), 1.0f, 2.0f, 30u, 30u, &mesh, nullptr );
	}

	Application::~Application()
	{
	}


// Functions:

	int32 Application::Run()
	{
		while ( true ) // CONDITION REQUIRED!!!
		{
		// Process all messages pending, but to not block for new messages:

			if ( const auto ecode = dx9::Window::ProcessMessages() )
			{
			// If return optional has value, means we're quitting so return exit code
				
				return *ecode;
			}
			
			this->DoFrame();

		// Limit cpu cycles to ~ 60 frames per second:

			Sleep(15);
		}
	}


// Private Functions:

	void Application::DoFrame()
	{
		m_Window.GetRenderSystem().Render( mesh, 0.1f );
	}