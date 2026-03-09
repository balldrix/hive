#pragma once

#include "IEvent.h"

class RangedEnemy;

class FireProjectileEvent : public IEvent
{
public:
	FireProjectileEvent(RangedEnemy* enemy);
	~FireProjectileEvent() = default;

	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	RangedEnemy* m_enemy;
};
