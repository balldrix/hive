#ifndef _UNITVECTORS_H_
#define _UNITVECTORS_H_

#include "Vector2D.h"

// A list of unit vectors for 8 directions
// up, down, left, right and diaganols.

namespace directionNS
{
	// up
	const Vector2D UP = Vector2D(0.0f, -1.0f);
	
	// down
	const Vector2D DOWN = Vector2D(0.0f, 1.0f);
	
	// left
	const Vector2D LEFT = Vector2D(-1.0f, 0.0f);
	
	// right
	const Vector2D RIGHT = Vector2D(1.0f, 0.0f);
	
	// upleft
	const Vector2D UPLEFT = Vector2D(-0.707f, -0.707f);
	
	// upright
	const Vector2D UPRIGHT = Vector2D(0.707f, -0.707f);
	
	// downleft
	const Vector2D DOWNLEFT = Vector2D(-0.707f, 0.707f);
	
	// downright
	const Vector2D DOWNRIGHT = Vector2D(0.707f, 0.707f);
}


#endif	_UNITVECTORS_H_