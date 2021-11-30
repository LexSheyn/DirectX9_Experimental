#ifndef WINDOW_H
#define WINDOW_H

#include "../InputDevices/Keyboard/Keyboard.h"
#include "../InputDevices/Mouse/Mouse.h"

#include "../RenderSystem/RenderSystem.h"

namespace dx9
{
	class Window
	{
	public:

	// Constructors and Destructor:

		Window(int32 width, int32 height, const char* name);
		Window(const Window&) = delete;

		~Window();

	// Functions:

		static std::optional<int32> ProcessMessages() noexcept;

	// Accessors:

		RenderSystem& GetRenderSystem();

	// Modifiers:

		void SetTitle(const std::string& title);

	// Operators:

		Window& operator=(const Window&) = delete;

	// Components:

		Keyboard keyboard;
		Mouse    mouse;

	private:

	// Private Functions:

		static LRESULT __stdcall HandleMessageSetup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

		static LRESULT __stdcall HandleMessageThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

		LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

		// Variables:

		int32 m_Width;
		int32 m_Height;

		HWND m_hWnd;

		std::unique_ptr<RenderSystem> m_pRenderSystem;

	// Private WindowClass:

		// Singleton manages registration/cleanup of window class.
		class WindowClass
		{
		public:

		// Accessors:

			static const char* GetName() noexcept;

			static HINSTANCE   GetInstance() noexcept;

		private:

		// Private Constructors and Destructor:

			WindowClass() noexcept;
			WindowClass(const WindowClass&) = delete;

			~WindowClass();

		// Private Operators:

			WindowClass& operator=(const WindowClass&) = delete;

		// Variables:

			static constexpr const char* wndClassName = "DirectX9_Window";

			static WindowClass wndClass;

			HINSTANCE hInstance;
		};

	};
}

#endif // WINDOW_H