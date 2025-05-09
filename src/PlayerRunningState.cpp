#include "playerRunningState.h"

#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerSprintingState.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

PlayerRunningState* PlayerRunningState::Instance()
{
	static PlayerRunningState instance("run");
	return &instance;
}

void PlayerRunningState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
}

void PlayerRunningState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
			player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());

	if(player->GetMovementSpeed() == player->GetRunSpeed())
		player->GetStateMachine()->ChangeState((PlayerSprintingState::Instance()));

	if(player->IsGrounded())
		player->PlayFootstepSound();
}

void PlayerRunningState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}

PlayerRunningState::PlayerRunningState(const std::string &name)
{
	m_name = name;
}
