#pragma once

#include "oxy/Core/Base.h"
#include "oxy/Platform/WindowBackend.h"

#include <string>

namespace oxy {
	
	class Window
	{
	public:
		Window( const std::string& title, int width, int height, bool fullscreen = false );
		~Window();

	private:
		Backend_Window* m_BackendData = nullptr;

		std::string m_Title = "";
	};
}