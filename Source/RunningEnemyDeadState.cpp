#include "RunningEnemyDeadState.h"

#include "Enemy.h"
#include "Animator.h"

RunningEnemyDeadState* RunningEnemyDeadState::Instance()
{
    static RunningEnemyDeadState instance("deadRun");
    return &instance;
}

void RunningEnemyDeadState::OnEnter(Enemy* enemy)
{
    enemy->GetAnimator()->Reset();
    enemy->GetAnimator()->SetAnimation(m_name);
    enemy->GetHitBoxManager()->KillAll();
    enemy->SetTargetVelocity(Vector2::Zero);
}

void RunningEnemyDeadState::Execute(Enemy* enemy)
{
}

void RunningEnemyDeadState::OnExit(Enemy* enemy)
{
}

RunningEnemyDeadState::RunningEnemyDeadState(const std::string& name)
{
    m_name = name;
}
