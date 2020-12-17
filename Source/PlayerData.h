// PlayerData.h
// Christopher Ball 2020
// stores player data

#ifndef _PLAYERDATA_H_
#define _PLAYERDATA_H_

#include "GameObject.h"

struct PlayerData
{
	ObjectData objectData;
	float deathTime = 0.0f;
	float knockoutDuration = 0.0f;
};

#endif // !_PLAYERDATA_H_
