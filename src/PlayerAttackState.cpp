#include "PlayerAttackState.h"

#include "Animator.h"
#include "ControlSystem.h"
#include "GameObject.h"
#include "HitBoxManager.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "Sprite.h"
#include "StateMachine.h"
#include "Logger.h"
#include "SpriteSheet.h"

PlayerAttackState* PlayerAttackState::Instance()
{
	static PlayerAttackState instance;
	return &instance;
}

void PlayerAttackState::SetAttack(const std::string &name)
{
	m_name = name;
}

void PlayerAttackState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	player->GetControlSystem()->SetCanAttack(false);
	player->GetControlSystem()->IncrementComboCount();
}

void PlayerAttackState::Execute(Player* player)
{
	player->SetTargetVelocity(Vector2::Zero);
	player->SetCurrentVelocity(Vector2::Zero);

	if(player->GetAnimator()->GetCurrentFrame() == player->GetAnimator()->GetAnimation().frameCount - 1)
	{
		player->GetControlSystem()->SetCanAttack(true);
	}

	if(player->GetAnimator()->IsDone())
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerAttackState::OnExit(Player* player) { }

PlayerAttackState::PlayerAttackState(const std::string &name)
{
	m_name = name;
}