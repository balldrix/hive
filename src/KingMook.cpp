#include "KingMook.h"

#include "Animator.h"
#include "AssetLoader.h"
#include "EnemyAttackState.h"
#include "Randomiser.h"
#include "SoundSource.h"
#include "StateMachine.h"

#include <cstdint>
#include <string>

KingMook::~KingMook()
{
}

void KingMook::Attack()
{
	int randomNum = Randomiser::GetRandNumUniform(0, 1);
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
	std::string soundName = "boss_entrance_001";
	m_vocalSoundSource->Play(AssetLoader::GetSound(soundName));
}

void KingMook::PlayFootstepSound()
{
	if(m_recentFootstepFrame == m_animator->GetCurrentFrame())
		return;

	m_recentFootstepFrame = m_animator->GetCurrentFrame();

	uint32_t randomWalkIndex = Randomiser::GetRandNumUniform(1, 3);

	std::string soundName = "boss_walk_00" + std::to_string(randomWalkIndex);
	m_footStepSoundSource->Play(AssetLoader::GetSound(soundName));
}

void KingMook::PlayAttackSound()
{
	uint32_t randomWalkIndex = Randomiser::GetRandNumUniform(1, 4);

	std::string soundName = "boss_punch_00" + std::to_string(randomWalkIndex);
	m_attackSoundSource->Play(AssetLoader::GetSound(soundName));
}
