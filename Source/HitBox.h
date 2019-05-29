// HitBox.h
// Christopher Ball 2019
// hitbox data and texture

#ifndef _HITBOX_H_
#define _HITBOX_H_

#include "pch.h"
#include "AABB.h"
#include "Sprite.h"

// forward declarations
class Graphics;
class AABB;

class HitBox
{
public:
	HitBox();
	~HitBox();

	void Init(Sprite* sprite, AABB box, Color colour);	// initialise hitbox
	void Update(const Vector2& position);		// update hitbox mesh position
	void Render(Graphics* graphics);			// render hibox

	AABB GetAABB() const { return m_boundingBox; }

	void SetAABB(const AABB& boundingBox);
	void SetFlipped(bool flipped);

	AABB FlipAABB();
	AABB FlipAABB(const AABB& box);

	bool OnCollision(const HitBox &collider); // checks other hibox for collision
	bool OnCollision(const Vector2 &position); // checks vector position for collision

private:
	AABB m_boundingBox;		// aabb bounding box
	Sprite m_sprite;		// hitbox 
	Vector2 m_position;		// hit box position
	Color m_colour;			// vertex colour
	bool m_flipped;			// flipped hitbox
};

#endif _HITBOX_H_