#pragma once

#include "GameObject.h"

struct PlayerData
{
	ObjectData objectData;
	float deathTime = 0.0f;
	float knockoutDuration = 0.0f;
};