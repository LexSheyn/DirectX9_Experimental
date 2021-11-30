#include "../PrecompiledHeaders/stdafx.h"

#include "../Application/Application.h"

int32 __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int32 nCmdShow)
{
	// Create Window:

	try
	{
		return dx9::Application().Run();
	}
	catch (const std::exception& exception)
	{
		MessageBoxA(nullptr, exception.what(), "Standatd Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}