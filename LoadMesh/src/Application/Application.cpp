#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1050, 450, "DirectX9_Test_Window" )
	{
		mesh = m_Window.GetRenderSystem().CreateMesh();

	//	m_Window.GetRenderSystem().CreateVertexBuffer();
	//	m_Window.GetRenderSystem().CreateIndexBuffer();
	//	m_Window.GetRenderSystem().CreateMaterial();
	//	m_Window.GetRenderSystem().CreateLight( D3DXVECTOR3( 0.0f, 0.3f, 0.25f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//	m_Window.GetRenderSystem().CreateTexture( "C:/TemporaryStorage/Geass_256x256.png" );
		m_Window.GetRenderSystem().SetView();

	//	D3DXCreateTorus( &m_Window.GetRenderSystem().GetDevice(), 1.0f, 2.0f, 30u, 30u, &mesh, nullptr );

	// Loading Mesh:

	//	dx9::MeshLoader mesh_loader( m_Window.GetHandle() );
	//
	//	bool8 result = false;
	//
	//	result = mesh_loader.Load( "C:/TemporaryStorage/ttt2/tttt.obj" );
	//
	//	if ( !result )
	//	{
	//		MessageBoxA( m_Window.GetHandle(), "MeshLoader::Load::Failed!", "Window Error", 0u );
	//	}
	//	else
	//	{
	//		MessageBoxA(m_Window.GetHandle(), "MeshLoader::Load::Successfull! Keep going!", "Window Error", 0u);
	//	}
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
		m_Window.GetRenderSystem().Render( mesh, 0.01f );
	//	m_Window.GetRenderSystem().Render( 0.01f );
	}