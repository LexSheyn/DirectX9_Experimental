#include "../PrecompiledHeaders/stdafx.h"
#include "Window.h"

namespace dx9
{
// Constructors and Destructor:

	Window::Window( int32 width, int32 height, const char* name )
		: m_Width( width ),
		  m_Height( height ),
		  m_hWnd( 0 )
	{
	// Calculate Window size based on desired client region size:

		HWND desktop_window = GetDesktopWindow();

		RECT desktop_rect = { 0 };

		GetWindowRect(desktop_window, &desktop_rect );

		RECT window_rect  = { 0 };

		window_rect.left   = 100u;
		window_rect.right  = width + window_rect.left;
		window_rect.top    = 100u;
		window_rect.bottom = height + window_rect.top;

		if ( !( AdjustWindowRect(&window_rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) ) )
		{
		//	m_WindowException.Except( __LINE__, __FILE__, GetLastError());
		}
;
	// Create Window and get hWnd:

		m_hWnd = CreateWindowA(WindowClass::GetName(),
			                   name,
			                   WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//			                   window_rect.left,  window_rect.top, 
	                           CW_USEDEFAULT, CW_USEDEFAULT,
			                   window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
			                   nullptr,
			                   nullptr,
			                   WindowClass::GetInstance(),
			                   this);

		if ( m_hWnd == nullptr )
		{
		//	m_WindowException.Except(__LINE__, __FILE__, GetLastError());
		}

	// Newly created window start of as hidden.
	// Show Window:

		if ( m_hWnd != nullptr )
		{
			ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		}		

	// Create graphics object:

		m_pRenderSystem = std::make_unique<RenderSystem>( m_hWnd, m_Width, m_Height );
	}

	Window::~Window()
	{
		DestroyWindow( m_hWnd );
	}


// Functions:

	std::optional<int32> Window::ProcessMessages() noexcept
	{
		MSG msg;

	// While queue has messages, remove and dispatch them (but do not block on empty queue):

		while ( PeekMessageA( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
		// Check for quit because peekmessage does not signal this via return value:

			if ( msg.message == WM_QUIT )
			{
			// Return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit:

				return static_cast<int32>( msg.wParam );
			}

		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs:

			TranslateMessage( &msg );
			DispatchMessageA( &msg );
		}

	// Return empty optional when not quitting app:

		return {};
	}


// Accessors:

	RenderSystem& Window::GetRenderSystem()
	{
		return *m_pRenderSystem;
	}

	const HWND& Window::GetHandle() const
	{
		return m_hWnd;
	}


// Modifiers:

	void Window::SetTitle(const std::string& title)
	{
		if ( SetWindowTextA( m_hWnd, title.c_str() ) == 0 )
		{
		//	m_WindowException.Except( __LINE__, __FILE__, GetLastError() );
		}
	}

// Private Functions:

	LRESULT __stdcall Window::HandleMessageSetup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
	// Use create parameter passed in from CreateWindow() to store Window class pointer:

		if ( message == WM_NCCREATE )
		{
		// Extract pointer to Window class from creation data:

			const CREATESTRUCTA* const pCreate = reinterpret_cast<CREATESTRUCTA*>( lParam );

			Window* const pWindow = static_cast<Window*>( pCreate->lpCreateParams );

		// Set WinAPI manager user data to store pointer to Window class:

			SetWindowLongPtrA( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( pWindow ) );

		// Set message proc to normal (non-setup) handler now that setup us finished:

			SetWindowLongPtrA( hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( &Window::HandleMessageThunk ));

		// Forwad message to Window class handler:

			return pWindow->HandleMessage( hWnd, message, wParam, lParam );
		}

	// If we get a message before the WM_NCCREATE message, handle with default handler:

		return DefWindowProcA( hWnd, message, wParam, lParam );
	}

	LRESULT __stdcall Window::HandleMessageThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
	// Rertrieve pointer to Window class:

		Window* const pWindow = reinterpret_cast<Window*>( GetWindowLongPtrA( hWnd, GWLP_USERDATA) );

	// Firward message to Window class handler:

		return pWindow->HandleMessage( hWnd, message, wParam, lParam );
	}

	LRESULT Window::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch ( message )
		{
		// We do not want the DefWindowProc to handle this message because
		// We want out destructor to destroy the window, se return 0 instread:

			case WM_CLOSE:
			{
				PostQuitMessage( 0 );

				return 0;
			}

			// ---------------- Keyboard Messages ---------------- Begin:

		// Clear key state when window loses focus to prevent input getting
		// stacked into last known state:

			case WM_KILLFOCUS:
			{
				keyboard.ClearState();

				break;
			}

			case WM_KEYDOWN: // Fall through
			case WM_SYSKEYDOWN:
			{
				if ( !(lParam & 0x40000000) || keyboard.AutorepeatIsEnabled() )
				{
					keyboard.OnKeyPress(static_cast<uint8>(wParam));
				}				

				break;
			}

			case WM_KEYUP: // Fall through
			case WM_SYSKEYUP:
			{
				keyboard.OnKeyRelease( static_cast<uint8>(wParam) );

				break;
			}

			case WM_CHAR:
			{
				keyboard.OnChar( static_cast<uint8>(wParam) );

				break;
			}

			// ---------------- Keyboard Messages ---------------- End.

			// ---------------- Mouse Messages ---------------- Begin:

			case WM_MOUSEMOVE:
			{
				const POINTS point = MAKEPOINTS( lParam );
				
				if ( ( point.x >= 0 && point.x < m_Width ) && ( point.y >= 0 && point.y < m_Height ) )
				{
				// In client region -> log move and log enter + capture mouse (if not previous...):

					mouse.OnMouseMove( point.x, point.y );

					if ( !mouse.IsInWindow() )
					{
						SetCapture( m_hWnd );

						mouse.OnMouseEnter();
					}
				}
				else
				{
				// Not in client region -> log move / maintain capture if bottom down:

					if ( wParam & ( MK_LBUTTON | MK_RBUTTON ) )
					{
						mouse.OnMouseMove( point.x, point.y );
					}
					else
					{
					// If button up -> release capture / log event for leaving:

						ReleaseCapture();

						mouse.OnMouseLeave();
					}
				}

				break;
			}

			case WM_LBUTTONDOWN:
			{
				const POINTS point = MAKEPOINTS( lParam );

				mouse.OnLeftPress( point.x, point.y );

				break;
			}

			case WM_LBUTTONUP:
			{
				const POINTS point = MAKEPOINTS( lParam );

				mouse.OnLeftRelease( point.x, point.y );

				break;
			}

			case WM_RBUTTONDOWN:
			{
				const POINTS point = MAKEPOINTS( lParam );

				mouse.OnRightPress( point.x, point.y );

				break;
			}

			case WM_RBUTTONUP:
			{
				const POINTS point = MAKEPOINTS( lParam );

				mouse.OnRightRelease( point.x, point.y );

				break;
			}

			case WM_MOUSEWHEEL:
			{
				const POINTS point = MAKEPOINTS( lParam );

				const int32 delta = GET_WHEEL_DELTA_WPARAM( wParam );

				mouse.OnWheelDelta( point.x, point.y, delta );

				break;
			}

			// ---------------- Mouse Messages ---------------- End.
		}

		return DefWindowProcA( hWnd, message, wParam, lParam );
	}


// ---------------------------------------- WindowClass ---------------------------------------- :

// Constructors and Destructor:

	Window::WindowClass Window::WindowClass::wndClass;

	Window::WindowClass::WindowClass() noexcept
		: hInstance( GetModuleHandleA( nullptr ) )
	{
		WNDCLASSEXA window_class = { 0 };

		window_class.cbSize        = sizeof( window_class );
		window_class.style         = CS_OWNDC;
		window_class.lpfnWndProc   = HandleMessageSetup;
		window_class.cbClsExtra    = 0;
		window_class.cbWndExtra    = 0;
		window_class.hInstance     = GetInstance();
		window_class.hIcon         = nullptr;//static_cast<HICON>(LoadImageA( hInstance, MAKEINTRESOURCEA( IDI_ICON1 ), IMAGE_ICON, 48, 48, 0 ));
		window_class.hCursor       = nullptr;
		window_class.hbrBackground = nullptr;
		window_class.hIconSm       = nullptr;//static_cast<HICON>(LoadImageA( hInstance, MAKEINTRESOURCEA( IDI_ICON1 ), IMAGE_ICON, 16, 16, 0 ));
		window_class.lpszMenuName  = nullptr;
		window_class.lpszClassName = GetName();
		
		RegisterClassExA( &window_class );
	}

	Window::WindowClass::~WindowClass()
	{
		UnregisterClassA( wndClassName, GetInstance() );
	}

	const char* Window::WindowClass::GetName() noexcept
	{
		return wndClassName;
	}

	HINSTANCE Window::WindowClass::GetInstance() noexcept
	{
		return wndClass.hInstance;
	}
}