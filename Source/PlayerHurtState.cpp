#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

PlayerHurtState* PlayerHurtState::Instance()
{
	static PlayerHurtState instance("hurt");
	return &instance;
}

void PlayerHurtState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->KillAll();
	player->SetHurtTimer(0.0f);
}

void PlayerHurtState::Execute(Player* player)
{
	if (player->GetHurtTimer() > 0.5f)
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerHurtState::OnExit(Player* player)
{
}

PlayerHurtState::PlayerHurtState(const std::string &name)
{
	m_name = name;
}
