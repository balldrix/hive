#include "WasteBossJabState.h"

#include "Animator.h"
#include "Enemy.h"
#include "HitBoxManager.h"
#include "StateMachine.h"
#include "WasteBossIdleState.h"

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

WasteBossJabState* WasteBossJabState::Instance()
{
	static WasteBossJabState instance("jab");
	return &instance;
}

void WasteBossJabState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	boss->SetTargetVelocity(Vector2::Zero);

	auto directionToTarget = boss->GetPlayerTarget()->GetPosition().x - boss->GetPositionX();
	boss->FlipHorizontally(directionToTarget < 0);
}

void WasteBossJabState::Execute(Enemy* boss)
{
	if(boss->GetAnimator()->IsDone())
	{
		boss->GetStateMachine()->ChangeState(WasteBossIdleState::Instance());
	}
}

void WasteBossJabState::OnExit(Enemy* boss)
{
}

WasteBossJabState::WasteBossJabState(const std::string& name)
{
	m_name = name;
}
