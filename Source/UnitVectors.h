#ifndef _UNITVECTORS_H_
#define _UNITVECTORS_H_

#include "pch.h"

// A list of unit vectors for 8 directions
// up, down, left, right and diaganols.

namespace UnitVectors
{
	// up
	const Vector2 Up = Vector2(0.0f, -1.0f);
	
	// down
	const Vector2 Down = Vector2(0.0f, 1.0f);
	
	// left
	const Vector2 Left = Vector2(-1.0f, 0.0f);
	
	// right
	const Vector2 Right = Vector2(1.0f, 0.0f);
	
	// upleft
	const Vector2 UpLeft = Vector2(-0.707f, -0.707f);
	
	// upright
	const Vector2 UpRight = Vector2(0.707f, -0.707f);
	
	// downleft
	const Vector2 DownLeft = Vector2(-0.707f, 0.707f);
	
	// downright
	const Vector2 DownRight = Vector2(0.707f, 0.707f);
}


#endif	_UNITVECTORS_H_