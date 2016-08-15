#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "Colours.h"

// game constants
namespace GlobalConstants
{
	const wchar_t		WINDOW_NAME[] = L"Hive";				// Title of window that shows in top bar
	const wchar_t		WND_CLASS_NAME[] = L"MyWndClass";				// name of class for creating a window
	const unsigned int		GAME_WIDTH		= 1280;
	const unsigned int		GAME_HEIGHT		= 720;
	const float				FRAME_RATE		= 200.0f;
	const float				MIN_FRAME_RATE	= 10.0f;					// the minimum frame rate
	const float				MIN_FRAME_TIME	= 1.0f / FRAME_RATE;		// minimum desired time for 1 frame
	const float				MAX_FRAME_TIME	= 1.0f / MIN_FRAME_RATE;	// maximum time used in calculations
}

// maximum number of enemies on screen
const unsigned int		MAX_ENEMY = 50;

#endif _CONSTANTS_H_