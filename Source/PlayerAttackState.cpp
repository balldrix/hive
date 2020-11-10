#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"
#include "PlayerAttackState.h"

PlayerAttackState* PlayerAttackState::Instance()
{
	static PlayerAttackState instance;
	return &instance;
}

void PlayerAttackState::SetAttack(std::string name)
{
	m_name = name;
}

void PlayerAttackState::OnEnter(Player* player)
{
	// set jab animation
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
	player->GetControlSystem()->CanAttack(false);
}

void PlayerAttackState::Execute(Player* player)
{
	// stop movement
	player->SetTargetVelocity(Vector2::Zero);
	player->SetCurrentVelocity(Vector2::Zero);

	// true if the jab animation is done
	if(player->GetAnimator()->IsDone())
	{
		// change back to idle state and reset control timers
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
		player->GetControlSystem()->ResetTimers();
		player->GetControlSystem()->IncrementComboCount();
	}
}

void PlayerAttackState::OnExit(Player* player)
{
}

PlayerAttackState::PlayerAttackState(std::string name)
{
	m_name = name;
}
