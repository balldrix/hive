#include "EnemyAttackRunState.h"

#include "Enemy.h"
#include "Animator.h"
#include "EnemyRunningState.h"
#include "StateMachine.h"

EnemyAttackRunState* EnemyAttackRunState::Instance()
{
    static EnemyAttackRunState instance("attackRun");
    return &instance;

}

void EnemyAttackRunState::OnEnter(Enemy* enemy)
{
    enemy->GetAnimator()->Reset();
    enemy->GetAnimator()->SetAnimation(m_name);
    enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
    enemy->SetMovementSpeed(enemy->GetData().chargeSpeed);
    enemy->PlayPunchSound();
}

void EnemyAttackRunState::Execute(Enemy* enemy)
{
    if(enemy->GetAnimator()->IsDone())
        enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
}

void EnemyAttackRunState::OnExit(Enemy* enemy)
{
}

EnemyAttackRunState::EnemyAttackRunState(const std::string& name)
{
    m_name = name;
}
