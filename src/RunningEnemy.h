#pragma once

#include "Enemy.h"
#include "GameObject.h"

class RunningEnemy : public Enemy
{
public:
	RunningEnemy();
	~RunningEnemy();

	void ApplyDamage(GameObject* source, const int& amount);
	void Reset();
};