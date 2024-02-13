#include "PlayerOwnedStates.h"

#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "PlayerConstants.h"
#include "StateMachine.h"
#include "PlayerIdleState.h"

using namespace PlayerConstants;
using namespace DirectX::SimpleMath;

PlayerBlockState* PlayerBlockState::Instance()
{
	static PlayerBlockState instance("block");
	return &instance;
}

void PlayerBlockState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->SetTargetVelocity(Vector2::Zero);
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCurrentHitBox(m_name);
}

void PlayerBlockState::Execute(Player* player)
{
}

void PlayerBlockState::OnExit(Player* player)
{
	player->SetMovementSpeed(player->GetWalkSpeed());
}

PlayerBlockState::PlayerBlockState(const std::string& name)
{
	m_name = name;
}
