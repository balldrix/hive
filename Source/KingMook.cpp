#include "KingMook.h"

#include "Randomiser.h"
#include "EnemyOwnedStates.h"
#include "StateMachine.h"

KingMook::~KingMook()
{
}

void KingMook::Attack()
{
	int randomNum = Randomiser::Instance()->GetRandNum(0, 1);
	switch(randomNum)
	{
	case 0:
		EnemyAttackState::Instance()->SetAttack("Attack1");
		break;
	case 1:
		EnemyAttackState::Instance()->SetAttack("Attack2");
		break;
	default:
		EnemyAttackState::Instance()->SetAttack("Attack1");
		break;
	}

	m_stateMachine->ChangeState((EnemyAttackState::Instance()));
}