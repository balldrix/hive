#include "PlayerDodgeState.h"

#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "PlayerConstants.h"
#include "StateMachine.h"
#include "PlayerIdleState.h"

using namespace PlayerConstants;
using namespace DirectX::SimpleMath;

PlayerDodgeState* PlayerDodgeState::Instance()
{
	static PlayerDodgeState instance;
	return &instance;
}

void PlayerDodgeState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetHitBoxManager()->KillAll();
	
	Vector2 direction = player->GetCurrentVelocity();
	direction.Normalize();

	player->SetCurrentVelocity(direction * DodgeDirectionModifier);
	player->SetTargetVelocity(Vector2::Zero);
}

void PlayerDodgeState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero)
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
}

void PlayerDodgeState::OnExit(Player* player)
{
	player->SetMovementSpeed(player->GetWalkSpeed());
}
