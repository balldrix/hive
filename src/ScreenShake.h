#pragma once

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class Camera;

class ScreenShake
{
public:
	ScreenShake();
	~ScreenShake() = default;

	void Init(Camera* camera);
	void Update(float deltaTime);
	
	void Start(float intensity, float duration);
	Vector2 GetPositionOffset() const { return m_positionOffset; }

private:
	Camera* m_camera;
	float m_timer;
	float m_intensity;
	float m_duration;
	float m_isActive;
	Vector2 m_positionOffset;
};