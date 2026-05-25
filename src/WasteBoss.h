#pragma once

#include "Enemy.h"

class WasteBoss : public Enemy
{
public:
	WasteBoss() : Enemy() {}
	virtual ~WasteBoss();

	virtual void Attack() override;

private:
	virtual void ApplyDamage(GameObject* source, const DamageData& damageData) override;
};