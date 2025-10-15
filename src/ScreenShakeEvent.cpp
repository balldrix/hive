#include "ScreenShakeEvent.h"

#include "IEvent.h"
#include "Logger.h"
#include "ScreenShake.h"

#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>
#include <variant>

ScreenShakeEvent::ScreenShakeEvent(ScreenShake* screenShake) :
	IEvent(),
	m_screenShake(screenShake)
{
}

ScreenShakeEvent::~ScreenShakeEvent()
{
}

void ScreenShakeEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<DirectX::XMFLOAT2>(arg))
	{
		Logger::LogError("[ScreenShakeEvent] [OnStart] Incorrect argument, needs XMFLOAT2");	
		return;
	}

	Vector2 v = std::get<DirectX::XMFLOAT2>(arg);
	m_screenShake->Start(v.x, v.y);
	m_hasStarted = true;
	m_isComplete = false;
}

void ScreenShakeEvent::OnUpdate(float deltaTime)
{
	if(m_screenShake->IsActive()) return;

	m_isComplete = true;
}
