#pragma once

#include "Enemy.h"

#include "DamageData.h"
#include "GameObject.h"

class WasteBoss : public Enemy
{
public:
	WasteBoss() : Enemy() {}
	virtual ~WasteBoss();

	virtual void Attack() override;
	virtual bool TryHandleAttackHit(GameObject* target) override;

private:
	virtual void ApplyDamage(GameObject* source, const DamageData& damageData) override;
};