// Window Example
#include "oxy/Window.h"

void ResizeEvent( int w, int h ) 
{
	printf( "ResizeEvent: %d %d\n", w, h );
}

void MouseMoved( int x, int y ) 
{
	printf( "MouseMoved: %d %d\n", x, y );
}

int main() 
{
	oxy::Window* Window = new oxy::Window( "Hello World", 800, 600 );
	Window->SetResizeFunc( ResizeEvent );
	Window->SetMouseMovedFunc( MouseMoved );

	while( !Window->ShouldClose() )
	{
		Window->PollEvents();
	}

	delete Window;
}