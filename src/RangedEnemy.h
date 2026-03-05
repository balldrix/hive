#pragma once

#include "Enemy.h"

class RangedEnemy : public Enemy
{
public:
	RangedEnemy();
	~RangedEnemy();
	void Attack() override;
};