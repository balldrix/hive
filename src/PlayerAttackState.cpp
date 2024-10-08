#include "PlayerAttackState.h"

#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"
#include "AudioEngine.h"
#include "Sprite.h"

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

	player->PlayPunchSound(m_name);

	Animation currentAnimation = *player->GetAnimator()->GetAnimation();
	int endXPos = currentAnimation.endXPos;

	if(endXPos == 0)
		return;

	player->GetShadow()->DisableSprite();
}

void PlayerAttackState::Execute(Player* player)
{
	player->SetTargetVelocity(Vector2::Zero);
	player->SetCurrentVelocity(Vector2::Zero);

	if(player->GetAnimator()->GetCurrentFrame() == player->GetAnimator()->GetAnimation()->frameCount - 1)
	{
		player->GetControlSystem()->SetCanAttack(true);
	}

	if(player->GetAnimator()->IsDone())
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerAttackState::OnExit(Player* player)
{
	Animation currentAnimation = *player->GetAnimator()->GetAnimation();
	int endXPos = currentAnimation.endXPos;

	if(endXPos == 0)
		return;
	
	endXPos *= (int)player->GetFacingDirection().x;	
	player->SetPositionX(player->GetPositionX() + endXPos);
	player->GetShadow()->EnableSprite();
}

PlayerAttackState::PlayerAttackState(const std::string &name)
{
	m_name = name;
}