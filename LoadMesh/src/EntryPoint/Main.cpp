#include "../PrecompiledHeaders/stdafx.h"

#include "../Application/Application.h"

int32 __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int32 nCmdShow)
{
// Create Console:

//	AllocConsole();
//
//    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
//    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
//    FILE* hf_out = _fdopen(hCrt, "w");
//    setvbuf(hf_out, NULL, _IONBF, 1);
//    *stdout = *hf_out;
//
//    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
//    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
//    FILE* hf_in = _fdopen(hCrt, "r");
//    setvbuf(hf_in, NULL, _IONBF, 128);
//    *stdin = *hf_in;

    // Console has been created but it does not work...

// Create Window:

	Application().Run();

//	try
//	{
//		return Application().Run();
//	}
//	catch (const std::exception& exception)
//	{
//		MessageBoxA(nullptr, exception.what(), "Standatd Exception", MB_OK | MB_ICONEXCLAMATION);
//	}
//	catch (...)
//	{
//		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
//	}
//	return -1;

	return 0;
}