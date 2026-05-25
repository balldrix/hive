#include "WastesBossHurtState.h"

#include "Animator.h"
#include "Enemy.h"
#include "WasteBossIdleState.h"

WasteBossHurtState* WasteBossHurtState::Instance()
{
	static WasteBossHurtState instance("hurt");
	return &instance;
}

void WasteBossHurtState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	boss->ResetStateChangeTimer();
}

void WasteBossHurtState::Execute(Enemy* boss)
{
	if(boss->GetPlayerTarget()->GetHitBoxManager()->IsHitBoxActive() == false)
		boss->GetStateMachine()->ChangeState(WasteBossIdleState::Instance());
}

void WasteBossHurtState::OnExit(Enemy* boss)
{
}

WasteBossHurtState::WasteBossHurtState(const std::string& name)
{
	m_name = name;
}
