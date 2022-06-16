#pragma once

#include "oxy/Core/Base.h"
#include "oxy/Platform/WindowBackend.h"

#include <string>
#include <functional>

namespace oxy {
	
	// Window resize function type.
	using WindowResizeFunc = std::function<void( int, int )>;
	using WindowCloseFunc = std::function<void()>;
	using WindowKeyPressedFunc = std::function<void( uint32_t )>;
	using WindowKeyReleasedFunc = std::function<void( uint32_t )>;
	using WindowKeyDownFunc = std::function<void( uint32_t )>;
	using WindowMouseMoveFunc = std::function<void( int, int )>;

	struct CallbackFunctions
	{
		WindowResizeFunc ResizeFunc;
		WindowCloseFunc CloseFunc;
		WindowKeyPressedFunc KeyPressedFunc;
		WindowKeyReleasedFunc KeyReleasedFunc;
		WindowKeyDownFunc KeyDownFunc;
		WindowMouseMoveFunc MouseMoveFunc;
	};
}

namespace oxy {
	
	class Window
	{
	public:
		Window( const std::string& title, int width, int height, bool fullscreen = false );
		~Window();

		void PollEvents();

		// Does not do anything right now.
		void SetTitle( const std::string& title ) { m_Title = title; }
		void SetSize( int width, int height ) { m_Width = width; m_Height = height; }
		void SetFullscreen( bool fullscreen ) { m_Fullscreen = fullscreen; }
		
		// Set window callback functions.
		void SetResizeFunc( WindowResizeFunc func ) { m_Callbacks.ResizeFunc = func; }
		void SetCloseFunc( WindowCloseFunc func ) { m_Callbacks.CloseFunc = func; }
		void SetKeyPressedFunc( WindowKeyPressedFunc func ) { m_Callbacks.KeyPressedFunc = func; }
		void SetKeyReleasedFunc( WindowKeyReleasedFunc func ) { m_Callbacks.KeyReleasedFunc = func; }
		void SetKeyDownFunc( WindowKeyDownFunc func ) { m_Callbacks.KeyDownFunc = func; }
		void SetMouseMovedFunc( WindowMouseMoveFunc func ) { m_Callbacks.MouseMoveFunc = func; }

		bool ShouldClose() { return m_BackendData->ShouldClose; }

	private:
		int m_Width = 0;
		int m_Height = 0;
		std::string m_Title = "";
		bool m_Fullscreen = false;

		Backend_Window* m_BackendData = nullptr;
		CallbackFunctions m_Callbacks;
	private:
		friend class Backend_Window;
	};
}