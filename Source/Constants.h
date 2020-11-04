#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace GlobalConstants
{
	const wchar_t			WINDOW_NAME[]		= L"Hive";				// title of window that shows in top bar
	const wchar_t			WND_CLASS_NAME[]	= L"MyWndClass";		// name of class for creating a window
	const unsigned int		WND_WIDTH			= 960;					// window width
	const unsigned int		WND_HEIGHT			= 640;					// window height
	const unsigned int		GAME_WIDTH			= 120;					// game width
	const unsigned int		GAME_HEIGHT			= 80;					// game height
	const float				BACK_COLOUR[4]		= { 0.3f, 0.3f, 0.3f, 0.0f };// colour of window backPath// constants
	const float Gravity							= 2.0f;
}

namespace InGameHudConstants
{
	const unsigned int HealthBarPositionX = 11;
	const unsigned int HealthBarPositionY = 8;
	const unsigned int EnemyHealthBarPositionY = 18;
	const unsigned int EnemyPortraitPositionX = 2;
	const unsigned int EnemyPortraitPositionY = 14;
}

#endif _CONSTANTS_H_