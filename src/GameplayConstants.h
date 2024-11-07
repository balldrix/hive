#pragma once

#include <string>

namespace GameplayConstants
{
	const float VerticalHitRange = 8.0f;
	const float	Gravity = 4.0f;
	const float StartingBoundaryMinX = 1.0f;
	const float StartingBoundaryMinY = 76.0f;
	const float StartingBoundaryMaxY = 110.0f;

	const std::string HitBoxName = "hitbox";
	const std::string HurtBoxName = "hurtbox";
	const std::string PushBoxName = "pushbox";
}