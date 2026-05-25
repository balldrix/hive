#include "WasteBoss.h"

#include "DamageData.h"
#include "GameObject.h"
#include "Randomiser.h"
#include "WasteBossJabState.h"
#include "WasteBossSlamState.h"

WasteBoss::~WasteBoss()
{
}

void WasteBoss::ApplyDamage(GameObject* source, const DamageData& damageData)
{
	m_health -= damageData.amount;

	if(m_health < 0) m_health = 0;

	PlayImpactSound();
}

void WasteBoss::Attack()
{
	auto rand = Randomiser::GetRandNumNormal(0.0f, 1.0f);

	if(rand > 0.9f) GetStateMachine()->ChangeState(WasteBossSlamState::Instance());
	else GetStateMachine()->ChangeState(WasteBossJabState::Instance());
}