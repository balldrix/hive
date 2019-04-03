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

namespace
{
	struct HitBoxData
	{
		std::string	name;
		AABB movementBox;
		HurtBoxData hurtBox;
		AABB hitBox;
	};

	struct HurtBoxData
	{

	};

	void from_json(const json& j, HitBoxData& a)
	{
		a.name = j.at("name").get<std::string>();
		a.spriteSheetIndex = j.at("index").get<int>();
		a.frameCount = j.at("frameCount").get<int>();
		a.framesPerSecond = j.at("framesPerSecond").get<int>();
		a.loop = j.at("loop").get<bool>();
	}
}

class HitBox
{
public:
	HitBox();
	~HitBox();

	void Init(Sprite* sprite, Color colour);	// initialise hitbox
	void Update(const Vector2& position);		// update hitbox mesh position
	void Render(Graphics* graphics);			// render hibox

	AABB GetAABB() const { return m_boundingBox; }

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