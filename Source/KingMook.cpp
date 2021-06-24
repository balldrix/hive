#include "KingMook.h"

#include "Randomiser.h"
#include "EnemyOwnedStates.h"
#include "StateMachine.h"
#include "SoundSource.h"
#include "SoundManager.h"
#include "Animator.h"

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

void KingMook::PlayEntranceSound()
{
	std::wstring soundName = L"boss_entrance_001";
	m_vocalSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void KingMook::PlayWalkingSound()
{
	if(m_recentFootstepFrame == m_animator->GetCurrentFrame())
		return;

	m_recentFootstepFrame = m_animator->GetCurrentFrame();

	uint32_t randomWalkIndex = Randomiser::Instance()->GetRandNum(1, 3);

	std::wstring soundName = L"boss_walk_00" + std::to_wstring(randomWalkIndex);
	m_footStepsSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void KingMook::PlayPunchSound()
{
	uint32_t randomWalkIndex = Randomiser::Instance()->GetRandNum(1, 4);

	std::wstring soundName = L"boss_punch_00" + std::to_wstring(randomWalkIndex);
	m_punchSoundSource->SetSound(SoundManager::GetSound(soundName));
}
