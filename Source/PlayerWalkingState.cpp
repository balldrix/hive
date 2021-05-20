#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerWalkingState* PlayerWalkingState::Instance()
{
	static PlayerWalkingState instance("Walking");
	return &instance;
}

void PlayerWalkingState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
	player->SetMovementSpeed(player->GetWalkSpeed());
}

void PlayerWalkingState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerWalkingState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}

PlayerWalkingState::PlayerWalkingState(const std::string &name)
{
	m_name = name;
}
