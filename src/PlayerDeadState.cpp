#include "PlayerDeadState.h"

#include "Animator.h"
#include "HitBoxManager.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <string>

PlayerDeadState* PlayerDeadState::Instance()
{
	static PlayerDeadState instance("dead");
	return &instance;
}

PlayerDeadState::PlayerDeadState(const std::string &name)
{
	m_name = name;
}

void PlayerDeadState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	player->ResetKnockoutTimer();
	player->PlayDeathSound();
}

void PlayerDeadState::Execute(Player* player)
{
	player->SetVelocity(Vector2::Zero);
}

void PlayerDeadState::OnExit(Player* player)
{
}
