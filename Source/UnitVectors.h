#ifndef _UNITVECTORS_H_
#define _UNITVECTORS_H_

#include "pch.h"

// A list of unit vectors for 8 directions
// up, down, left, right and diaganols.

namespace Direction
{
	// up
	const Vector2 UP = Vector2(0.0f, -1.0f);
	
	// down
	const Vector2 DOWN = Vector2(0.0f, 1.0f);
	
	// left
	const Vector2 LEFT = Vector2(-1.0f, 0.0f);
	
	// right
	const Vector2 RIGHT = Vector2(1.0f, 0.0f);
	
	// upleft
	const Vector2 UPLEFT = Vector2(-0.707f, -0.707f);
	
	// upright
	const Vector2 UPRIGHT = Vector2(0.707f, -0.707f);
	
	// downleft
	const Vector2 DOWNLEFT = Vector2(-0.707f, 0.707f);
	
	// downright
	const Vector2 DOWNRIGHT = Vector2(0.707f, 0.707f);
}


#endif	_UNITVECTORS_H_