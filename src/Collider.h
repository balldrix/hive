#pragma once

#include "pch.h"
#include "AABB.h"
#include "Sprite.h"

// forward declarations
class Graphics;
class AABB;

class Collider
{
public:
	Collider();
	~Collider();

	void Init(Sprite* sprite, Color colour);	
	void Update(const Vector2& position);
	void Render(Graphics* graphics, const Vector2& position);

	AABB GetAABB() const { return m_boundingBox; }

	void SetAABB(const AABB& boundingBox);
	void SetFlipped(bool flipped);

	AABB FlipAABB();
	AABB FlipAABB(const AABB& box);

	bool OnCollision(const Collider &collider); 
	bool OnCollision(const Vector2 &position);

	void Delete();

private:
	AABB m_boundingBox;	
	Sprite* m_sprite;	
	Vector2 m_position;	
	Color m_colour;		
	bool m_flipped;		
};