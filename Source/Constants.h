#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "Colours.h"

// game constants
namespace GlobalConstants
{
	const wchar_t			WINDOW_NAME[]		= L"Hive";				// title of window that shows in top bar
	const wchar_t			WND_CLASS_NAME[]	= L"MyWndClass";		// name of class for creating a window
	const unsigned int		WND_WIDTH			= 960;					// window width
	const unsigned int		WND_HEIGHT			=540;					// window height
	const unsigned int		GAME_WIDTH			= 480;					// game width
	const unsigned int		GAME_HEIGHT			= 270;					// game height
}

#endif _CONSTANTS_H_