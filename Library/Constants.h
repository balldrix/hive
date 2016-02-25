#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "Colours.h"

// game constants
const char				GAME_NAME[]		= "Hive";
const char				CLASS_NAME[]	= "Kaon Engine";
const unsigned int		GAME_WIDTH		= 1280;
const unsigned int		GAME_HEIGHT		= 720;
const bool				FULLSCREEN		= false;

const float				FRAME_RATE		= 200.0f;
const float				MIN_FRAME_RATE	= 10.0f;					// the minimum frame rate
const float				MIN_FRAME_TIME	= 1.0f / FRAME_RATE;		// minimum desired time for 1 frame
const float				MAX_FRAME_TIME	= 1.0f / MIN_FRAME_RATE;	// maximum time used in calculations

const double			PI				= 3.14159265;

const float				KEY_DELAY		= 5.0f;

const int				TILE_SIZE		= 32;

// maximum number of enemies on screen
const unsigned int		MAX_ENEMY = 50;

#endif _CONSTANTS_H_