#include "../PrecompiledHeaders/stdafx.h"
#include "Menu.h"

namespace dx9
{
// Constructors and Destructor:

	Menu::Menu( HWND phWnd, IDirect3DDevice9* pD3DDevice )
	{
	// Create context and set I/O:

		ImGui::CreateContext();

		static ImGuiIO& io = ImGui::GetIO();

	// Get window handle and direct 3d device:

		ImGui_ImplWin32_Init( phWnd );

		ImGui_ImplDX9_Init( pD3DDevice );
	}

	Menu::~Menu()
	{
		ImGui_ImplDX9_Shutdown();

		ImGui_ImplWin32_Shutdown();

		ImGui::DestroyContext();
	}


// Functions:

	void Menu::Draw()
	{
	// Feed inputs to dead imgui, start new frame:

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

	// Any application code here:

		ImGui::Text( "That's GUI!" );

	// Render dear imgui into screen:

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );
	}

}