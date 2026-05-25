#include "WasteBossApproachState.h"

#include "Enemy.h"
#include "GameplayConstants.h"

#include <cmath>
#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;
using namespace GameplayConstants;

namespace
{
	constexpr float VerticalAlignmentSnapRange = 1.0f;
}

WasteBossApproachState* WasteBossApproachState::Instance()
{
	static WasteBossApproachState instance("walk");
	return &instance;
}

void WasteBossApproachState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	boss->ResetStateChangeTimer();
	boss->SetMovementSpeed(boss->GetData().walkSpeed);
}

void WasteBossApproachState::Execute(Enemy* boss)
{
	if(boss->GetHealth() < 1) return;

	const Vector2 bossPosition = boss->GetPosition();
	const Vector2 playerPosition = boss->GetPlayerTarget()->GetPosition();
	const float deltaX = playerPosition.x - bossPosition.x;
	const float deltaY = playerPosition.y - bossPosition.y;
	const float distance = (bossPosition - playerPosition).Length();
	const float verticalDistance = fabs(deltaY);

	if(distance <= boss->GetData().attackRange && verticalDistance <= VerticalAlignmentSnapRange)
	{
		boss->SetPositionY(playerPosition.y);
		boss->Stop();
		boss->Attack();
		return;
	}

	Vector2 direction = Vector2::Zero;

	if(distance > boss->GetData().attackRange)
	{
		direction.x = deltaX > 0.0f ? 1.0f : -1.0f;
	}

	if(verticalDistance > VerticalAlignmentSnapRange)
	{
		direction.y = deltaY > 0.0f ? 1.0f : -1.0f;
	}

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}

	boss->SetTargetVelocity(direction);
}

void WasteBossApproachState::OnExit(Enemy* boss)
{
}

WasteBossApproachState::WasteBossApproachState(const std::string& name)
{
	m_name = name;
}
