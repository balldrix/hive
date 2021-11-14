#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Animator.h"
#include "StateMachine.h"

PlayerRunningState* PlayerRunningState::Instance()
{
	static PlayerRunningState instance("Running");
	return &instance;
}

void PlayerRunningState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
}

void PlayerRunningState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());

	if(player->IsGrounded())
		player->PlayWalkingSound();
}

void PlayerRunningState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}

PlayerRunningState::PlayerRunningState(const std::string &name)
{
	m_name = name;
}