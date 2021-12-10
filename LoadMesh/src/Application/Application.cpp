#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1154, 630, "DirectX9_Test_Window" )
	{
	// Loading Mesh:

	//	m_OBJLoader.LoadOBJ( "D:/Models/robot_triangulated/robot_triangulated.obj", true );
		m_OBJLoader.LoadMaterial( "D:/Models/Technovotum/material_1.mtl" );
		m_OBJLoader.LoadMaterial( "D:/Models/Technovotum/material_2.mtl" );

		m_STLLoader.LoadSTL( "D:/Models/Technovotum/VTM_VTP_ASCII.STL" );
		
	//	Meshes[0].CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), m_OBJLoader.GetVertices(), m_OBJLoader.GetFacesAmount() );
	//	Meshes[0].CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), m_STLLoader.GetVertices(), m_STLLoader.GetFacesAmount() );

	// TEST ---------------------------------------------------------------------------------:

		std::vector<dx9::Vertex> vertices_1;

		vertices_1.resize( 4170u ); // v 8340, f 2780

		for ( size_t i = 0u; i < 4170u ; i++ )
		{
			vertices_1[i] = m_STLLoader.GetVertices().at( i );
		}

		std::vector<dx9::Vertex> vertices_2;

		vertices_2.resize( 4170u );

		for ( size_t i = 0u; i < 4170u; i++ )
		{
			vertices_2[i] = m_STLLoader.GetVertices().at( i + 4170u );
		}

		Meshes[0].CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), vertices_1, 1390u );
		Meshes[1].CreateVertexBuffer( m_Window.GetRenderSystem().GetDevice(), vertices_2, 1390u );

		Meshes[0].SetMaterial(m_OBJLoader.GetMaterials().at( 0 ));
		Meshes[1].SetMaterial(m_OBJLoader.GetMaterials().at( 1 ));

	// --------------------------------------------------------------------------------------		

	//	m_Window.GetRenderSystem().AddToQueue( &Meshes[0] );
	//	m_Window.GetRenderSystem().AddToQueue( &Meshes[1] );

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
	// Set World transformation matrix:

		m_Window.GetRenderSystem().SetTransformationFromInput( 0.1f );

	// Render:

		m_Window.GetRenderSystem().Clear();

		m_Window.GetRenderSystem().Render( Meshes[0] ); // 1 draw call
		m_Window.GetRenderSystem().Render( Meshes[1] ); // 2 draw call

		m_Window.GetRenderSystem().Display();
	}