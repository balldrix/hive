#include "KingMookChargeState.h"

#include "Enemy.h"
#include "Animator.h"
#include "Player.h"

KingMookChargeState* KingMookChargeState::Instance()
{
    static KingMookChargeState instance("Attack3");
    return &instance;
}

KingMookChargeState::KingMookChargeState(std::string name)
{
	m_name = name;
}

void KingMookChargeState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);

	Vector2 direction = enemy->GetPlayerTarget()->GetPosition() - enemy->GetPosition();
	enemy->SetTargetVelocity(Vector2::Zero);
	enemy->SetTargetVelocityX(direction.x * enemy->GetData().chargeSpeed);
}

void KingMookChargeState::Execute(Enemy* enemy)
{
}

void KingMookChargeState::OnExit(Enemy* enemy)
{
}
