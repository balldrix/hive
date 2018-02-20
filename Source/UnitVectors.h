#ifndef _UNITVECTORS_H_
#define _UNITVECTORS_H_

#include "pch.h"

// A list of unit vectors for 8 directions
// up, down, left, right and diaganols.

namespace directionNS
{
	// up
	const Vector2 UP = Vector2(0.0f, -0.5f);
	
	// down
	const Vector2 DOWN = Vector2(0.0f, 0.5f);
	
	// left
	const Vector2 LEFT = Vector2(-1.0f, 0.0f);
	
	// right
	const Vector2 RIGHT = Vector2(1.0f, 0.0f);
	
	// upleft
	const Vector2 UPLEFT = Vector2(-0.707f, -0.5f);
	
	// upright
	const Vector2 UPRIGHT = Vector2(0.707f, -0.5f);
	
	// downleft
	const Vector2 DOWNLEFT = Vector2(-0.707f, 0.5f);
	
	// downright
	const Vector2 DOWNRIGHT = Vector2(0.707f, 0.5f);
}


#endif	_UNITVECTORS_H_