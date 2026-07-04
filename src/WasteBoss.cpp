#include "WasteBoss.h"

#include "DamageData.h"
#include "EnemyDeadState.h"
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

	if(m_health == 0 && !m_stateMachine->IsInState(*EnemyDeadState::Instance()))
	{
		Kill();
		m_stateMachine->ChangeState(EnemyDeadState::Instance());
	}
}

void WasteBoss::Attack()
{
	GetStateMachine()->ChangeState(WasteBossJabState::Instance());
}

bool WasteBoss::TryHandleAttackHit(GameObject* target)
{
	if(!m_stateMachine->IsInState(*WasteBossJabState::Instance()))
		return false;

	if(target != m_playerTarget || m_playerTarget->GetHealth() <= 0)
		return false;

	const float roll = Randomiser::GetRandNumUniform(0.0f, 1.0f);

	if(roll <= 0.9f)
		return false;

	m_stateMachine->ChangeState(WasteBossSlamState::Instance());
	return true; // Slam consumed the jab hit
}