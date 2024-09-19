#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerIdleState::PlayerIdleState(const std::string &name)
{
	m_name = name;
}

PlayerIdleState* PlayerIdleState::Instance()
{
	static PlayerIdleState instance("idle");
	return &instance;
}

void PlayerIdleState::OnEnter(Player* player)
{
	player->ResetKnockoutTimer();
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	player->GetControlSystem()->SetCanAttack(true);
}

void PlayerIdleState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero)
		return;

	if(player->GetMovementSpeed() == player->GetWalkSpeed())
		player->GetStateMachine()->ChangeState((PlayerRunningState::Instance()));

	if(player->GetMovementSpeed() == player->GetRunSpeed())
		player->GetStateMachine()->ChangeState((PlayerSprintingState::Instance()));
}

void PlayerIdleState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}
