#include "PlayerSprintingState.h"

#include "Animator.h"
#include "Player.h"
#include "PlayerIdleState.h"
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
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
}

void PlayerSprintingState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
}

void PlayerSprintingState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}

PlayerSprintingState::PlayerSprintingState(const std::string &name)
{
	m_name = name;
}