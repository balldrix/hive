#pragma once

#include "Enemy.h"

class WasteBoss : public Enemy
{
public:
	WasteBoss() : Enemy() {}
	virtual ~WasteBoss();

	virtual void Attack();
};