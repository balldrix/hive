#pragma once

#include "Enemy.h"

class RunningEnemy : public Enemy
{
public:
	
	RunningEnemy();

	void ApplyDamage(GameObject* source, const int& amount);
	void Reset();
};