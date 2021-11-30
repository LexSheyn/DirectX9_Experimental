#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

namespace dx9
{
// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1050, 450, "DirectX9_Test_Window" )
	{
		m_Window.GetRenderSystem().CreateVertexBuffer();
		m_Window.GetRenderSystem().CreateIndexBuffer();
		m_Window.GetRenderSystem().SetView();

		D3DXCreateTorus( &m_Window.GetRenderSystem().GetDevice(), 1.0f, 2.0f, 30u, 30u, &mesh, nullptr );
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

			if ( const auto ecode = Window::ProcessMessages() )
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
	}

}