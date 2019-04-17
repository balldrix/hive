#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerIdleState::PlayerIdleState(std::string name)
{
	m_name = name;
}

PlayerIdleState* PlayerIdleState::Instance()
{
	static PlayerIdleState instance("Idle");
	return &instance;
}

void PlayerIdleState::OnEnter(Player* player)
{
	// set idle animation
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
}

void PlayerIdleState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() != Vector2::Zero)
	{
		player->GetStateMachine()->ChangeState((PlayerWalkingState::Instance()));
	}
}

void PlayerIdleState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}
