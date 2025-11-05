#pragma once

#include <string>

namespace GameplayConstants
{
	const float VerticalHitRange = 5.0f;
	const float	Gravity = 4.0f;
	const int GameplayBoundsUpperY = 72;
	const int GameplayBoundsLowerY = 115;
	const float MinEnemyAvoidDistance = 15.0f;

	const std::string HitBoxName = "hitbox";
	const std::string HurtBoxName = "hurtbox";
	const std::string PushBoxName = "pushbox";

	const std::string UpperBoundsId = "upper bounds";
	const std::string LowerBoundsId = "lower bounds";
	const std::string LeftBoundsId = "left bounds";
	const std::string RightBoundsId = "right bounds";

	const float EnemyDeadDuration = 4.0f;
	const float EnemyFlashStartTime = 1.0f;
	const float EnemyFlashDuration = 0.2f;
}