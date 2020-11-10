#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

PlayerHurtState* PlayerHurtState::Instance()
{
	static PlayerHurtState instance("Hurt");
	return &instance;
}

void PlayerHurtState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->KillAll();
}

void PlayerHurtState::Execute(Player* player)
{
	if(player->GetAnimator()->IsDone())
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}


void PlayerHurtState::OnExit(Player* player)
{
}

PlayerHurtState::PlayerHurtState(std::string name)
{
	m_name = name;
}
