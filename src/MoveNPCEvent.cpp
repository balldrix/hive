#include "MoveNPCEvent.h"

#include "Enemy.h"
#include "IEvent.h"
#include "Logger.h"

#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>
#include <variant>

MoveNPCEvent::MoveNPCEvent(Enemy* enemy) :
	IEvent(),
	m_enemy(enemy)
{
}

MoveNPCEvent::~MoveNPCEvent()
{
}

void MoveNPCEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<DirectX::XMFLOAT2>(arg))
	{
		Logger::LogError("[MoveNPCEvent] [OnStart] Incorrect argument, needs XMFLOAT2");
		return;
	}

	m_destination = std::get<DirectX::XMFLOAT2>(arg);
	m_enemy->GetAnimator()->SetAnimation("walk");
	m_hasStarted = true;
}

void MoveNPCEvent::OnUpdate(float deltaTime)
{
	auto groundPosition = m_enemy->GetGroundPosition();
	Vector2 direction = m_destination - groundPosition;
	direction.Normalize();
	m_enemy->SetTargetVelocity(direction * m_enemy->GetMovementSpeed());
	m_enemy->ApplyFacingDirection();

	if((m_destination - groundPosition).Length() > 1.0f) return;

	m_isComplete = true;
	m_enemy->SetVelocity(Vector2::Zero);
	m_enemy->GetAnimator()->SetAnimation("idle");
}