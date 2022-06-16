#pragma once

#include <stdint.h>

namespace oxy {
	
	enum class MouseButtonState : uint32_t {
		None = 0,
		Pressed = 1,
		Released = 2,
		Repeated = 3
	};
	
	enum class MouseButton : uint32_t 
	{
		Left = 0,
		Right = 1,
		Middle = 2,

		// Extra buttons
		X1 = 3,
		X2 = 4,
		X3 = 5,		
		X4 = 5,	
		X5 = 6		
	};
}