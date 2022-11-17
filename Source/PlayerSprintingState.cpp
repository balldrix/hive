#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Animator.h"
#include "StateMachine.h"

PlayerSprintingState* PlayerSprintingState::Instance()
{
	static PlayerSprintingState instance("sprint");
	return &instance;
}

void PlayerSprintingState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
}

void PlayerSprintingState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());

	if(player->IsGrounded())
		player->PlayWalkingSound();
}

void PlayerSprintingState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}

PlayerSprintingState::PlayerSprintingState(const std::string &name)
{
	m_name = name;
}