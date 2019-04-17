#include "PlayerOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"
#include "PlayerJabState.h"

PlayerJabState* PlayerJabState::Instance()
{
	static PlayerJabState instance("Jab");
	return &instance;
}

void PlayerJabState::OnEnter(Player* player)
{
	// set jab animation
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
	player->GetControlSystem()->CanAttack(false);
}

void PlayerJabState::Execute(Player* player)
{
	// stop movement
	player->SetTargetVelocity(Vector2::Zero);
	player->SetCurrentVelocity(Vector2::Zero);

	// true if the jab animation is done
	if(player->GetAnimator()->IsDone())
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerJabState::OnExit(Player* player)
{
}

PlayerJabState::PlayerJabState(std::string name)
{
	m_name = name;
}
