#pragma once

// Backend code for windows, code for windows, code for linux, etc...

#include "oxy/Core/Base.h"

#include <string>

namespace oxy {
	
	struct Backend_Window
	{
#if defined( _WIN32 )
		HWND Handle = nullptr;
		HINSTANCE Instance = nullptr;
		HDC DeviceContext = nullptr;
		HGLRC OpenGLContext = nullptr;
#else
		xcb_connection_t* Connection;
		xcb_window_t Window;
		xcb_gc_t GraphicsContext;
		xcb_screen_t* Screen;
#endif
	};

	extern Backend_Window* Backend_CreateWindow( const std::string& title, int width, int height );
	extern void Backend_DestroyWindow( Backend_Window* Window );
}