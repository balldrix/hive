#include "PlayerPickupState.h"

#include "Animator.h"
#include "Player.h"
#include "PlayerIdleState.h"

#include <directxtk/SimpleMath.h>
#include <string>

PlayerPickupState::PlayerPickupState(const std::string& name)
{
	m_name = name;
}

PlayerPickupState* PlayerPickupState::Instance()
{
	static PlayerPickupState instance("pickup");
	return &instance;
}

void PlayerPickupState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	player->PlaySound("pickup_001");
	player->SetTargetVelocity(Vector2::Zero);
}

void PlayerPickupState::Execute(Player* player)
{
	if(player->GetAnimator()->IsDone())
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerPickupState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}
