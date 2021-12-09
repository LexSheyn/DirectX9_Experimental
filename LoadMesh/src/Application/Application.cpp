#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1154, 630, "DirectX9_Test_Window" )
	{
	// Loading Mesh:

	//	m_OBJLoader.LoadOBJ( "D:/Models/robot_triangulated/robot_triangulated.obj", true );
		m_OBJLoader.LoadMaterial( "D:/Models/robot_triangulated/robot_triangulated.mtl" );

		m_STLLoader.LoadSTL( "D:/Models/Technovotum/VTM_VTP_ASCII.STL" );
		
	//	TestMesh.CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), m_OBJLoader.GetVertices(), m_OBJLoader.GetFacesAmount() );
		TestMesh.CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), m_STLLoader.GetVertices(), m_STLLoader.GetFacesAmount() );

		TestMesh.SetMaterial( m_OBJLoader.GetMaterials().at( 0u ) );

		D3DXVECTOR3 lightPosition = { 0.0f, 0.0f, -100.0f };

		m_Window.GetRenderSystem().CreateLight( lightPosition, dx9::Color::White );

		m_Window.GetRenderSystem().SetView( 0.0f );
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
		m_Window.GetRenderSystem().Render( TestMesh, 0.1f );
	}