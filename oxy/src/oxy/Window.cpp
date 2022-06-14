#include "Window.h"

namespace oxy {
	
	Window::Window( const std::string& title, int width, int height, bool fullscreen /*= false */ )
		: m_Title( title )
	{
		m_BackendData = Backend_CreateWindow( m_Title, width, height );
	}

	Window::~Window()
	{
		Backend_DestroyWindow( m_BackendData );
	}
}