#include "ScreenShake.h"

#include "Camera.h"
#include "Randomiser.h"

#include <cmath>
#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

ScreenShake::ScreenShake() :
	m_camera(nullptr),
	m_duration(0.0f),
	m_intensity(0.0f),
	m_timer(0.0f),
	m_isActive(false)
{
}

void ScreenShake::Init(Camera* camera)
{
	m_camera = camera;
}

void ScreenShake::Update(float deltaTime)
{
	if(!m_isActive) return;

	if(m_timer > 0.0f)
	{
		m_positionOffset = Vector2::Zero;
		m_positionOffset.x += Randomiser::Instance()->GetRandNumUniform(-1.0f, 1.0f) * m_intensity;
		m_positionOffset.y += Randomiser::Instance()->GetRandNumUniform(-1.0f, 1.0f) * m_intensity;
		m_timer -= deltaTime;
		m_intensity = std::lerp(m_intensity, 0.0f, 1 - m_timer / m_duration);
		return;
	}

	m_timer = 0.0f;
	m_isActive = false;
}

void ScreenShake::Start(float intensity, float duration)
{
	m_duration = duration;
	m_timer = duration;
	m_intensity = intensity;
	m_isActive = true;
}