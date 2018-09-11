// HitBox.h
// Christopher Ball 2018
// hitbox data and texture

#ifndef _HITBOX_H_
#define _HITBOX_H_

#include "pch.h"
#include "AABB.h"

// forward declarations
class Graphics;
class AABB;
class Sprite;

class HitBox
{
public:
	HitBox();
	~HitBox();

	void Init(Sprite* sprite, Color colour);	// initialise hitbox
	void Update(const Vector2& position);		// update hitbox mesh position
	void Render(Graphics* graphics);			// render hibox

	void SetAABB(const AABB& boundingBox);
	void SetFlipped(bool flipped);

	AABB FlipAABB();

private:
	AABB m_boundingBox;		// aabb bouding box
	Sprite* m_sprite;		// hitbox 
	Vector2 m_position;		// hit box position
	Color m_colour;			// vertex colour
	bool m_flipped;			// flipped hitbox
};

#endif _HITBOXMESH_H_