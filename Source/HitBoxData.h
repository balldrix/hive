// HitBoxData.h
// Christopher Ball 2019
// stores hitbox data using json

#include "pch.h"
#include "AABB.h"

#ifndef _HITBOXDATA_H_
#define _HITBOXDATA_H_

namespace
{
	struct HitBoxData
	{
		std::string	name; // name of hitbox data should be same as animation state name
		AABB movementBox; // hit box to block movement in scene
		AABB hitBox; // hit box (red) is what will do damage to other character
		AABB hurtBox; // hit box that set character's vulnerable area
		int startupFrames = 0;
		int activeFrames = 0;
	};

	void from_json(const json& j, HitBoxData& a)
	{
		a.name = j.at("name").get<std::string>();
		a.startupFrames = j.at("startup").get<int>();
		a.activeFrames = j.at("active").get<int>();

		// movement box data
		json movement = j["movementBox"];
		a.movementBox.SetMin(Vector2(movement["minX"], movement["minY"]));
		a.movementBox.SetMax(Vector2(movement["maxX"], movement["maxY"]));

		// hitbox data
		json hits = j["hitBox"];
		a.hitBox.SetMin(Vector2(hits["minX"], hits["minY"]));
		a.hitBox.SetMax(Vector2(hits["maxX"], hits["maxY"]));

		// hurt box data
		json hurts = j["hurtBox"];
		a.hurtBox.SetMin(Vector2(hurts["minX"], hurts["minY"]));
		a.hurtBox.SetMax(Vector2(hurts["maxX"], hurts["maxY"]));
	}
}

#endif // !_HITBOXDATA_H_