#pragma once

// Backend code for windows, code for windows, code for linux, etc...

#include "oxy/Core/Base.h"

#include <string>

namespace oxy {
	
	class Window;

	class Backend_Window
	{
	public:
		Backend_Window( Window* owner, const std::string& title, int width, int height );
		~Backend_Window() {}

		void PollEvents();

	public:
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
		bool ShouldClose = false;

	private:
		WNDPROC OldWindowProc = nullptr;
		static LRESULT WindowProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam );

	private:
		friend class Window;
	};
}