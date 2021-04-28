#pragma once

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
	Sprite m_spriteSheet;		// hitbox 
	Vector2 m_position;		// hit box position
	Color m_colour;			// vertex colour
	bool m_flipped;			// flipped hitbox
};