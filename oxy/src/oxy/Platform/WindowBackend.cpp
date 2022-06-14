#include "WindowBackend.h"

#include <stdio.h>

namespace oxy {
	
#if defined( _WIN32 )
	namespace Windows {
		// Window Proc
		LRESULT CALLBACK WindowProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam ) 
		{
			switch( Msg )
			{
				case WM_CREATE:
					printf( "WM_CREATE\n" );
					break;
			}

			return DefWindowProc( hwnd, Msg, wParam, lParam );
		}

		static void RegisterWindowClass() 
		{
			const wchar_t CLASS_NAME[] = L"Oxy Window class";

			WNDCLASS wc = {};
			wc.lpfnWndProc = WindowProc;
			wc.hInstance = GetModuleHandle( nullptr );
			wc.lpszClassName = CLASS_NAME;

			RegisterClass( &wc );
		}

		static void UnregisterWindowClass() 
		{
			UnregisterClass( L"Oxy Window class", GetModuleHandle( nullptr ) );
		}
	}
#endif

	Backend_Window* Backend_CreateWindow( const std::string& title, int width, int height )
	{
		Backend_Window* window = new Backend_Window();
		
#if defined( _WIN32 )

		Windows::RegisterWindowClass();

		window->Instance = GetModuleHandle( nullptr );
		window->Handle = CreateWindowEx
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
			window->Instance,
			nullptr
		);

		ShowWindow( window->Handle, 1 );
		
#else
#endif

		return window;
	}

	void Backend_DestroyWindow( Backend_Window* window )
	{
#if defined( _WIN32 )
		DestroyWindow( window->Handle );
#else
#endif
		window->Handle = nullptr;
		window->Instance = nullptr;

		delete window;
	}

}