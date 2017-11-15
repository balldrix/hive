#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "Colours.h"

// game constants
namespace GlobalConstants
{
	const wchar_t			WINDOW_NAME[]		= L"Hive";				// title of window that shows in top bar
	const wchar_t			WND_CLASS_NAME[]	= L"MyWndClass";		// name of class for creating a window
	const unsigned int		WND_WIDTH			= 1024;					// window width
	const unsigned int		WND_HEIGHT			= 576;					// window height
	const unsigned int		GAME_WIDTH			= 256;					// game width
	const unsigned int		GAME_HEIGHT			= 144;					// game height
	const float				BACK_COLOUR[4] = { 0.3f, 0.3f, 0.3f, 0.0f };// colour of window backPath
}

#endif _CONSTANTS_H_