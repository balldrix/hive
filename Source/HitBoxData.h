#include "pch.h"
#include "AABB.h"

#pragma once

namespace
{
	struct HitBoxData
	{
		std::string	name; 
		AABB movementBox; 
		AABB hitBox; 
		AABB hurtBox; 
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