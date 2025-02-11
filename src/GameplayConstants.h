#pragma once

#include <string>

namespace GameplayConstants
{
	const float VerticalHitRange = 8.0f;
	const float	Gravity = 4.0f;
	const int GameplayBoundsUpperY = 72;
	const int GameplayBoundsLowerY = 115;
	const float MinEnemyAvoidDistance = 15.0f;
	const float MaxEnemyAttackDistance = 10.0f;

	const std::string HitBoxName = "hitbox";
	const std::string HurtBoxName = "hurtbox";
	const std::string PushBoxName = "pushbox";

	const std::string UpperBoundsId = "upper bounds";
	const std::string LowerBoundsId = "lower bounds";
	const std::string LeftBoundsId = "left bounds";
	const std::string RightBoundsId = "right bounds";
}