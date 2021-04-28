#pragma once

#include "Enemy.h"

class KingMook : public Enemy
{
public:
	KingMook() : Enemy() {}
	virtual ~KingMook();

	virtual void Attack();
};