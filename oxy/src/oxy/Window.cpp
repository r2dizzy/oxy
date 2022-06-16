#include "Window.h"

namespace oxy {
	
	Window::Window( const std::string& title, int width, int height, bool fullscreen /*= false */ )
		: m_Title( title ), m_Width( width ), m_Height( height ), m_Fullscreen( fullscreen )
	{
		m_BackendData = new Backend_Window( this, m_Title, width, height );
	}

	Window::~Window()
	{
		delete m_BackendData;
	}

	void Window::PollEvents()
	{
		m_BackendData->PollEvents();
	}

}