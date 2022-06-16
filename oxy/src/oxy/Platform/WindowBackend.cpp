#include "WindowBackend.h"
#include "oxy/Window.h"

#include <windowsx.h>

#include <stdio.h>

namespace oxy {
	
#if defined( _WIN32 )
	namespace Windows {
		// Default Window Proc
		LRESULT CALLBACK _WindowProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
		{
			return DefWindowProc( hwnd, Msg, wParam, lParam );
		}

		static void RegisterWindowClass() 
		{
			const wchar_t CLASS_NAME[] = L"Oxy Window class";

			WNDCLASS wc = {};
			wc.lpfnWndProc = _WindowProc;
			wc.hInstance = GetModuleHandle( nullptr );
			wc.lpszClassName = CLASS_NAME;

			RegisterClass( &wc );
		}

		static void UnregisterWindowClass() 
		{
			UnregisterClass( L"Oxy Window class", GetModuleHandle( nullptr ) );
		}

		static void PollEvents() 
		{
			MSG msg;
			while ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
	}
#endif

	Backend_Window::Backend_Window( Window* owner, const std::string& title, int width, int height )
	{
#if defined( _WIN32 )
		Windows::RegisterWindowClass();
		
		Instance = GetModuleHandle( nullptr );
		Handle = CreateWindowEx
		(
			0,
			L"Oxy Window class",
			L"Oxy Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			nullptr,
			nullptr,
			Instance,
			nullptr
		);

		// Set user data using GWLP_USERDATA
		SetWindowLongPtr( Handle, GWLP_USERDATA, ( LONG_PTR ) owner );

		// Override the window proc to our window proc.
		OldWindowProc = ( WNDPROC )SetWindowLongPtr( Handle, GWLP_WNDPROC, ( LONG_PTR )WindowProc );

		SetPropW( Handle, L"OxyWindow_Backend", ( HANDLE ) this );

		ShowWindow( Handle, 1 );
		UpdateWindow( Handle );
#else
#endif
	}

	void Backend_Window::PollEvents()
	{
#if defined( _WIN32 )
		Windows::PollEvents();
#else
#endif
	}

	LRESULT Backend_Window::WindowProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
	{
		Window* window = ( Window* ) GetWindowLongPtr( hwnd, GWLP_USERDATA );

		Backend_Window* backend = ( Backend_Window* ) GetPropW( hwnd, L"OxyWindow_Backend" );

		switch( Msg )
		{
			case WM_CREATE:
				printf( "WM_CREATE\n" );
				break;

			case WM_CLOSE:
				backend->ShouldClose = true;
				break;

			// Resize.
			case WM_SIZE:
			{
				int width = LOWORD( lParam );
				int height = HIWORD( lParam );
				
				if( window->m_Callbacks.ResizeFunc )
					window->m_Callbacks.ResizeFunc( width, height );
				
			} break;

			// Mouse move.
			case WM_MOUSEMOVE:
			{
				int x = GET_X_LPARAM( lParam );
				int y = GET_Y_LPARAM( lParam );
				
				if( window->m_Callbacks.MouseMoveFunc )
					window->m_Callbacks.MouseMoveFunc( x, y );
				
			} break;

			// Mouse down.
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				
			} break;
		}

		// Hand off to the default window proc.
		return CallWindowProc( backend->OldWindowProc, hwnd, Msg, wParam, lParam );
	}

}