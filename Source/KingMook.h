// Christopher Ball 2019-2021

#pragma once

#include "Enemy.h"

class KingMook : public Enemy
{
public:
	KingMook() : Enemy() {}
	virtual ~KingMook();

	virtual void Attack();
};