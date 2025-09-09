#include "PlayerBlockState.h"

#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <string>

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
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
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
